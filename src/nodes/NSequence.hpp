#ifndef NSEQUENCE_HPP_
#define NSEQUENCE_HPP_

#include "NBlock.hpp"
#include "NBlockish.hpp"
#include "SymTable.h"
#include "Outputter.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

struct NSequence : public NBlockish {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NSequence();

    NSequence(const unsigned rung_count);

    // Copy constructor
    NSequence(const NSequence& other);

    // Move constructor
    NSequence(NSequence&& other);

    // Destructor
    ~NSequence();

    // Assignment operator
    NSequence&
    operator=(const NSequence& other);

    // Move assignment operator
    NSequence&
    operator=(NSequence&& other);
    /* }}} */

    virtual SymTable&
    populate_symtable(SymTable& symtable) const override;

    virtual std::string
    to_verilog(const SymTable& symtable) const override;

    virtual std::string
    to_dot(Outputter& outputter, const SymTable& symtable) const override;

    virtual bool
    is_output() const override;

    std::vector<NBlockish*> blocks;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NSequence::NSequence()
    : NBlockish{NBlockish::BlockType::SEQUENCE, 0}
    , blocks{std::vector<NBlockish*>{}}
{
}

inline
NSequence::NSequence(const unsigned rung_count)
    : NBlockish{NBlockish::BlockType::SEQUENCE, rung_count}
    , blocks{std::vector<NBlockish*>{}}
{
}

// Copy constructor
inline
NSequence::NSequence(const NSequence& other)
    : NBlockish{other}
    , blocks{other.blocks}
{
}

// Move constructor
inline
NSequence::NSequence(NSequence&& other)
     : NBlockish{std::move(other)}
     , blocks{std::move(other.blocks)}
{
}

// Destructor
inline
NSequence::~NSequence()
{
}

// Assignment operator
inline NSequence&
NSequence::operator=(const NSequence& other) {
    Node::operator=(other);
    blocks = other.blocks;
    return *this;
}

// Move assignment operator
inline NSequence&
NSequence::operator=(NSequence&& other) {
    Node::operator=(std::move(other));
    blocks = std::move(other.blocks);
    return *this;
}
/* }}} */

inline SymTable&
NSequence::populate_symtable(SymTable& symtable) const {
    for (auto& block : blocks) {
        block->populate_symtable(symtable);
    }
    return symtable;
}

inline std::string
NSequence::to_verilog(const SymTable& symtable) const {
    std::ostringstream oss;
    oss << "(";
    for (unsigned i = 0; i < blocks.size(); i++) {
        oss << blocks[i]->to_verilog(symtable);

        // Join with & because this is a sequential connection
        if (i != blocks.size() - 1) {
            oss << " & ";
        }
    }
    oss << ")" << std::flush;

    return oss.str();
}

inline std::string
NSequence::to_dot(Outputter& outputter, const SymTable& symtable) const {
    // TODO: Implement me!
    ignore_unused_warnings(outputter);
    ignore_unused_warnings(symtable);
    return "Sorry, unimplemented";
}

inline bool
NSequence::is_output() const {
    auto l = [](const NBlockish* b) {
        return b->is_output();
    };
    return std::all_of(blocks.begin(), blocks.end(), l);
}

#endif /* end of include guard */
