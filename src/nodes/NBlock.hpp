#ifndef NBLOCK_HPP_
#define NBLOCK_HPP_

#include "NBlockish.hpp"
#include "NInstruction.hpp"
#include "NAddress.hpp"
#include "SymTable.h"
#include "Inst2Verilog.h"
#include "Outputter.h"

#include <cstdio>
#include <vector>
#include <string>

struct NBlock : public NBlockish {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NBlock();

    NBlock(const NInstruction* inst,
           const std::vector<NAddress*>& addresses,
           const unsigned rung_count);

    // Copy constructor
    NBlock(const NBlock& other);

    // Move constructor
    NBlock(NBlock&& other);

    // Destructor
    ~NBlock();

    // Assignment operator
    NBlock&
    operator=(const NBlock& other);

    // Move assignment operator
    NBlock&
    operator=(NBlock&& other);
    /* }}} */

    virtual SymTable&
    populate_symtable(SymTable& symtable) const override;

    virtual std::string
    to_verilog(const SymTable& symtable) const override;

    virtual std::string
    to_dot(Outputter& outputter, const SymTable& symtable) const override;

    virtual bool
    is_output() const override;

    NInstruction* inst;
    std::vector<NAddress*> addresses;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NBlock::NBlock()
    : NBlockish{NBlockish::BlockType::BLOCK, 0}
    , inst{nullptr}
    , addresses{nullptr}
{
}

inline
NBlock::NBlock(const NInstruction* inst,
               const std::vector<NAddress*>& addresses,
               const unsigned rung_count)
    : NBlockish{NBlockish::BlockType::BLOCK, rung_count}
    , inst{const_cast<NInstruction*>(inst)}
    , addresses{addresses}
{
}

// Copy constructor
inline
NBlock::NBlock(const NBlock& other)
    : NBlockish{other}
    , inst{other.inst}
    , addresses{other.addresses}
{
}

// Move constructor
inline
NBlock::NBlock(NBlock&& other)
    : NBlockish{std::move(other)}
    , inst{std::move(other.inst)}
    , addresses{std::move(other.addresses)}
{
}

// Destructor
inline
NBlock::~NBlock()
{
}

// Assignment operator
inline NBlock&
NBlock::operator=(const NBlock& other) {
    Node::operator=(other);
    inst = other.inst;
    addresses = other.addresses;
    return *this;
}

// Move assignment operator
inline NBlock&
NBlock::operator=(NBlock&& other) {
    Node::operator=(std::move(other));
    inst = std::move(other.inst);
    addresses = std::move(other.addresses);
    return *this;
}
/* }}} */

inline SymTable&
NBlock::populate_symtable(SymTable& symtable) const {
    for (unsigned i = 0; i < addresses.size(); i++) {
        // Check for output address indices
        auto type = (OUTPUT_INSTS.count(inst->name) != 0
                     && OUTPUT_INSTS.at(inst->name).count(i) != 0)
            ? SymTable::IOType::OUT
            : SymTable::IOType::IN;

        auto address_name = addresses[i]->name;
        // Note: The append method handles changing the pin type
        symtable[address_name].append(rung_count, type);
        // TODO: adjust bus width according to constants used?
    }

    // TODO: should intermediate `wire's be in the symtable? (like the ones used for timers)

    return symtable;
}

inline std::string
NBlock::to_verilog(const SymTable& symtable) const {
    // Convert to Verilog
    return Inst2Verilog(inst)(addresses, symtable);
}

inline std::string
NBlock::to_dot(Outputter& outputter, const SymTable& symtable) const {
    char buf[512];
    // TODO: element count
    std::sprintf(buf, "Block_%d_%d", rung_count, 42);
    outputter.append("nodes", buf);
    // TODO: add inst and addresses
    // outputter.append("nodes", node_name.str());
    // outputter.append("edges",
    // TODO: Implement me!
    ignore_unused_warnings(outputter);
    ignore_unused_warnings(symtable);
    return "Sorry, unimplemented";
}

inline bool
NBlock::is_output() const {
    return OUTPUT_INSTS.count(inst->name) != 0;
}

#endif /* end of include guard */
