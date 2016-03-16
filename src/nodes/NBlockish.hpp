#ifndef NBLOCKISH_HPP_
#define NBLOCKISH_HPP_

#include "Node.hpp"

/**
 * A structure that acts like blocks. These include NBlock, NSegment,
 * NParallel, and NSequence.
 */
struct NBlockish : public Node {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NBlockish();

    NBlockish(const unsigned rung_count);

    // Copy constructor
    NBlockish(const NBlockish& other);

    // Move constructor
    NBlockish(NBlockish&& other);

    // Destructor
    ~NBlockish();

    // Assignment operator
    NBlockish&
    operator=(const NBlockish& other);

    // Move assignment operator
    NBlockish&
    operator=(NBlockish&& other);
    /* }}} */
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NBlockish::NBlockish()
    : Node{}
{
}

inline
NBlockish::NBlockish(const unsigned rung_count)
    : Node{rung_count}
{
}

inline
// Copy constructor
NBlockish::NBlockish(const NBlockish& other)
    : Node{other}
{
}

// Move constructor
inline
NBlockish::NBlockish(NBlockish&& other)
    : Node{std::move(other)}
{
}

// Destructor
inline
NBlockish::~NBlockish()
{
}

// Assignment operator
inline NBlockish&
NBlockish::operator=(const NBlockish& other) {
    Node::operator=(other);
    return *this;
}

// Move assignment operator
inline NBlockish&
NBlockish::operator=(NBlockish&& other) {
    Node::operator=(std::move(other));
    return *this;
}
/* }}} */

#endif /* end of include guard */
