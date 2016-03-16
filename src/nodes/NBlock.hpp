#ifndef NBLOCK_HPP_
#define NBLOCK_HPP_

#include "NBlockish.hpp"
#include "NInstruction.hpp"
#include "NAddress.hpp"

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

#endif /* end of include guard */
