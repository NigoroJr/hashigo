#ifndef NSEQUENCE_HPP_
#define NSEQUENCE_HPP_

#include "NBlockish.hpp"

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

    std::vector<NBlockish*> blocks;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NSequence::NSequence()
    : NBlockish{0}
    , blocks{std::vector<NBlockish*>{}}
{
}

inline
NSequence::NSequence(const unsigned rung_count)
    : NBlockish{rung_count}
    , blocks{std::vector<NBlockish*>{}}
{
}

// Copy constructor
inline
NSequence::NSequence(const NSequence& other)
    : NBlockish{other.rung_count}
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

#endif /* end of include guard */
