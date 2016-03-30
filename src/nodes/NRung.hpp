#ifndef NRUNG_HPP_
#define NRUNG_HPP_

#include "Node.hpp"
#include "NBlock.hpp"
#include "NBlockish.hpp"
#include "NSequence.hpp"
#include "NSegment.hpp"
#include "NParallel.hpp"
#include "SymTable.h"
#include "Outputter.h"
#include "Block2Verilog.h"

#include <memory>
#include <utility>
#include <vector>
#include <queue>
#include <string>

struct NRung : public Node {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NRung();

    NRung(const NBlockish* b, const unsigned rung_count);

    // Copy constructor
    NRung(const NRung& other);

    // Move constructor
    NRung(NRung&& other);

    // Destructor
    ~NRung();

    // Assignment operator
    NRung&
    operator=(const NRung& other);

    // Move assignment operator
    NRung&
    operator=(NRung&& other);
    /* }}} */

    virtual SymTable&
    populate_symtable(SymTable& symtable) const override;

    /**
     * Determines the inputs and outputs of this rung.
     */
    void
    populate_in_out();

    /**
     * Overload so that the rung can append to the Outputter.
     *
     * Since the job of this method is to append to the Outputter, nothing is
     * returned.
     */
    void
    to_verilog(Outputter& outputter, const SymTable& symtable) const;

    virtual std::string
    to_dot(Outputter& outputter, const SymTable& symtable) const override;

    NBlockish* block;

    /**
     * The LHS and the RHS of the rung.
     * For example, if we had:
     *
     *     XIC(Foo) XIC(Bar) OTE(Baz)
     *
     * This will become an NSequence that contains {XIC(Foo), XIC(Bar} and the
     * outputs will become a vector of length 1 with {OTE(Baz)}. This is done
     * so that when converting to Verilog, the to_verilog method of the input
     * only needs to be called. The `outputs' is a vector because we could
     * have multiple outputs in parallel in a rung. However, note that we do
     * not currently allow multiple outputs in series.
     *
     * OK:
     *     XIC(Foo) [OTE(Bar), OTE(Baz)]
     * NG:
     *     XIC(Foo) [OTE(Bar) OTE(Baz)]
     *
     * The output Verilog will probably be weird if the latter is used.
     * TODO: Error message
     *
     * Also note that `inputs' is not in the AST (the AST contains data with
     * `inputs' and `outputs' connected together but not separately).
     * Separation is done in populate_in_out, which should be called some time
     * after the AST was constructed.
     */
    std::shared_ptr<NBlockish> inputs;
    std::vector<NBlock*> outputs;

private:

    /**
     * Finds the closest NSequence block in the AST.
     * In a proper Ladder Logic program, the nearest NSequence is almost
     * always the member variable `block' because a rung needs to have at
     * least one input and one output in series.
     */
    NSequence*
    find_nearest_sequence() const;

    /**
     * Decomposes the NBlockish passed in and returns a vector of all NBlock
     * contained as children.
     */
    std::vector<NBlock*>
    extract_blocks(NBlockish* blockish) const;

    std::string
    timer_module_verilog(const NBlock* output, const SymTable& symtable) const;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NRung::NRung()
    : Node{0}
    , block{nullptr}
{
}

inline
NRung::NRung(const NBlockish* b, const unsigned rung_count)
    : Node{rung_count}
    , block{const_cast<NBlockish*>(b)}
{
}

// Copy constructor
inline
NRung::NRung(const NRung& other)
    : Node{other}
    , block{other.block}
{
}

// Move constructor
inline
NRung::NRung(NRung&& other)
    : Node{std::move(other)}
    , block{std::move(other.block)}
{
}

// Destructor
inline
NRung::~NRung()
{
}

// Assignment operator
inline NRung&
NRung::operator=(const NRung& other) {
    Node::operator=(other);
    block = other.block;
    return *this;
}

// Move assignment operator
inline NRung&
NRung::operator=(NRung&& other) {
    Node::operator=(std::move(other));
    block = std::move(other.block);
    return *this;
}
/* }}} */

inline SymTable&
NRung::populate_symtable(SymTable& symtable) const {
    return block->populate_symtable(symtable);
}

inline void
NRung::populate_in_out() {
    // TODO: extract_blocks, find_nearest_sequence
    std::vector<NBlockish*> nearest_sequence = find_nearest_sequence()->blocks;

    // Reverse traverse sequence to find all outputs
    auto blockish_it = nearest_sequence.rbegin();
    // Expect this loop to run only one iteration
    while (blockish_it != nearest_sequence.rend()) {
        auto& blockish_ptr = *blockish_it;

        if (blockish_ptr->is_output()) {
            for (const auto& block : extract_blocks(blockish_ptr)) {
                outputs.insert(outputs.begin(), block);
            }
        }
        else {
            break;
        }
        blockish_it++;
    }

    // Rest is all inputs
    std::vector<NBlockish*> tmp_inputs;
    while (blockish_it != nearest_sequence.rend()) {
        tmp_inputs.insert(tmp_inputs.begin(), *blockish_it);
        blockish_it++;
    }

    // If tmp_inputs has only one element, use that as `inputs'.
    // Otherwise, make a new NSequence from all NBlockish in tmp_inputs
    if (tmp_inputs.size() == 1) {
        inputs = std::shared_ptr<NBlockish>{tmp_inputs.front()};
    }
    else {
        auto seq = new NSequence{rung_count};
        seq->blocks = std::move(tmp_inputs);
        inputs = std::shared_ptr<NBlockish>{seq};
    }
}

inline void
NRung::to_verilog(Outputter& outputter, const SymTable& symtable) const {
    for (const auto& output : outputs) {
        auto verilog =  Block2Verilog(output->inst->name)(inputs.get(),
                                                          output,
                                                          symtable);
        outputter.append("rungs", verilog);

        // Add Timer modules
        if (output->inst->name == "TON" || output->inst->name == "TOF") {
            auto modules = timer_module_verilog(output,symtable);
            outputter.append("modules", modules);
        }
    }
}

inline std::string
NRung::to_dot(Outputter& outputter, const SymTable& symtable) const {
    // TODO: Implement me!
    ignore_unused_warnings(outputter);
    ignore_unused_warnings(symtable);
    return "Sorry, unimplemented";
}

inline NSequence*
NRung::find_nearest_sequence() const {
    if (block->type == NBlockish::BlockType::SEQUENCE) {
        // This block is most likely going to be executed
        return dynamic_cast<NSequence*>(block);
    }
    else {
        // Do a BFS
        std::queue<NBlockish*> q;
        q.push(block);
        while (!q.empty()) {
            auto b = q.front();
            q.pop();
            if (b->type == NBlockish::BlockType::SEQUENCE) {
                return dynamic_cast<NSequence*>(b);
            }

            if (b->type == NBlockish::BlockType::PARALLEL) {
                auto p_block = dynamic_cast<NParallel*>(b);
                for (const auto& block : p_block->blocks) {
                    q.push(block);
                }
            }
            else if (b->type == NBlockish::BlockType::SEGMENT) {
                q.push(dynamic_cast<NSegment*>(b)->block);
            }
            else if (b->type == NBlockish::BlockType::BLOCK) {
                // Do nothing
            }
            else {
                throw std::runtime_error{"Unknown block type"};
            }
        }

        throw std::runtime_error{"No NSequence node found"};
    }
}

inline std::vector<NBlock*>
NRung::extract_blocks(NBlockish* blockish) const {
    std::vector<NBlock*> to_ret;

    // Do a BFS
    std::queue<NBlockish*> q;
    q.push(blockish);
    while (!q.empty()) {
        auto b = q.front();
        q.pop();
        switch (b->type) {
            case NBlockish::BlockType::SEQUENCE:
                for (const auto& block : dynamic_cast<NSequence*>(b)->blocks) {
                    q.push(block);
                }
                break;
            case NBlockish::BlockType::PARALLEL:
                for (const auto& block : dynamic_cast<NParallel*>(b)->blocks) {
                    q.push(block);
                }
                break;
            case NBlockish::BlockType::SEGMENT:
                q.push(dynamic_cast<NSegment*>(b)->block);
                break;
            case NBlockish::BlockType::BLOCK:
                to_ret.push_back(dynamic_cast<NBlock*>(b));
                break;
            default:
                throw std::runtime_error{"Unknown block type"};
        }
    }

    return to_ret;
}

inline std::string
NRung::timer_module_verilog(const NBlock* output,
                            const SymTable& symtable) const {
    /* Sample output Verilog:
     *   wire n_timer_2_done_wire;
     *   Timer t2(clk, rst, tick, 5000, main_wash, n_timer_2_done_wire);
     */

    auto timer_name = symtable[output->addresses[0]].var_name;
    // Milliseconds to wait
    auto preset = symtable[output->addresses[1]].var_name;
    auto enable_addr = symtable[output->addresses[3]].var_name;
    auto done_addr = symtable[output->addresses[5]].var_name;

    std::string wire_name = "n_" + done_addr + "_wire";

    std::stringstream oss;
    // Declare wire
    oss << "wire " << wire_name << ";" << std::endl;

    // Stamp out module
    char buf[512];
    std::sprintf(buf,
                 "Timer %s(clk, rst, tick, %s, %s, %s);",
                 timer_name.c_str(),
                 preset.c_str(),
                 enable_addr.c_str(),
                 wire_name.c_str());
    oss << buf;

    return oss.str();
}

#endif /* end of include guard */
