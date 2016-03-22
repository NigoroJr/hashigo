#ifndef NBLOCK_HPP_
#define NBLOCK_HPP_

#include "NBlockish.hpp"
#include "NInstruction.hpp"
#include "NAddress.hpp"
#include "SymTable.h"

#include <vector>

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

    NInstruction* inst;
    std::vector<NAddress*> addresses;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NBlock::NBlock()
    : NBlockish{0}
    , inst{nullptr}
    , addresses{nullptr}
{
}

inline
NBlock::NBlock(const NInstruction* inst,
               const std::vector<NAddress*>& addresses,
               const unsigned rung_count)
    : NBlockish{rung_count}
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
        auto type = (SymTable::OUTPUT_ADDRS.count(inst->name) != 0
                     && SymTable::OUTPUT_ADDRS.at(inst->name).count(i) != 0)
            ? SymTable::IOType::OUT
            : SymTable::IOType::IN;

        auto address_name = addresses[i]->name;
        // Note: The append method handles changing the pin type
        symtable[address_name].append(rung_count, type);
        // TODO: adjust bus width according to constants used?
    }

    // TODO: intermediate wires??? should this be in the symtable? (like the ones used for timers)
    // TODO: Master (for master, maybe add a MASTER instruction
    if (inst->name == "TON" || inst->name == "TOF") {
        // We need intermediate pins for Verilog
    }

    return symtable;
}

#endif /* end of include guard */
