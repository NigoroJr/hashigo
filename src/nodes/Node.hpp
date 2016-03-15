#ifndef NODE_HPP_
#define NODE_HPP_

#include "Visitor.h"

#include <stdexcept>
#include <utility>
#include <string>

/**
 * Base class for all the nodes in the Abstract Syntax Tree.
 */
struct Node {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    Node();

    Node(const unsigned rung_count);

    // Copy constructor
    Node(const Node& other);

    // Move constructor
    Node(Node&& other);

    // Destructor
    ~Node();

    // Assignment operator
    Node&
    operator=(const Node& other);

    // Move assignment operator
    Node&
    operator=(Node&& other);
    /* }}} */

    virtual Visitor&
    traverse(Visitor& visitor) const;

    unsigned rung_count;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
Node::Node()
    : rung_count{0}
{
}

inline
Node::Node(const unsigned rung_count)
    : rung_count{rung_count}
{
}

// Copy constructor
inline
Node::Node(const Node& other)
    : rung_count{other.rung_count}
{
}

// Move constructor
inline
Node::Node(Node&& other)
    : rung_count{std::move(other.rung_count)}
{
}

// Destructor
inline
Node::~Node()
{
}

// Assignment operator
inline Node&
Node::operator=(const Node& other) {
    rung_count = other.rung_count;
    return *this;
}

// Move assignment operator
inline Node&
Node::operator=(Node&& other) {
    rung_count = std::move(other.rung_count);
    return *this;
}
/* }}} */

inline Visitor&
Node::traverse(Visitor& visitor) const {
    throw std::runtime_error{"Sorry, uninplemented"};

    return visitor;
}

#endif /* end of include guard */
