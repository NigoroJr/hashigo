#ifndef NBLOCKISH_HPP_
#define NBLOCKISH_HPP_

#include "Node.hpp"

/**
 * A structure that acts like blocks. These include NBlock, NSegment,
 * NParallel, and NSequence.
 */
struct NBlockish : public Node {
    enum BlockType {
        BLOCK, SEGMENT, SEQUENCE, PARALLEL,
    };

    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NBlockish();

    NBlockish(const BlockType& type, const unsigned rung_count);

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

    BlockType type;

    /**
     * Checks whether this block-ish is an output or not.
     * A block-ish node is an output if all of the children that it contains
     * are output instructions.
     */
    virtual bool
    is_output() const = 0;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NBlockish::NBlockish()
    : Node{}
    , type{}
{
}

inline
NBlockish::NBlockish(const BlockType& type, const unsigned rung_count)
    : Node{rung_count}
    , type{type}
{
}

inline
// Copy constructor
NBlockish::NBlockish(const NBlockish& other)
    : Node{other}
    , type{other.type}
{
}

// Move constructor
inline
NBlockish::NBlockish(NBlockish&& other)
    : Node{std::move(other)}
    , type{std::move(other.type)}
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
    type = other.type;
    return *this;
}

// Move assignment operator
inline NBlockish&
NBlockish::operator=(NBlockish&& other) {
    Node::operator=(std::move(other));
    type = std::move(other.type);
    return *this;
}
/* }}} */

#endif /* end of include guard */
