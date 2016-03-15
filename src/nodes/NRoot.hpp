#ifndef NROOT_HPP_
#define NROOT_HPP_

#include "Node.hpp"
#include "NRung.hpp"
#include "Visitor.h"

#include <vector>

/**
 * The entry point of the AST. Since all the rungs are attached to this node,
 * there is no rung count.
 */
struct NRoot : public Node {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NRoot();

    // Copy constructor
    NRoot(const NRoot& other);

    // Move constructor
    NRoot(NRoot&& other);

    // Destructor
    ~NRoot();

    // Assignment operator
    NRoot&
    operator=(const NRoot& other);

    // Move assignment operator
    NRoot&
    operator=(NRoot&& other);
    /* }}} */

    Visitor&
    traverse(Visitor& visitor) const override;

    std::vector<NRung*> rungs;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NRoot::NRoot()
    : Node{}
{
}

// Copy constructor
inline
NRoot::NRoot(const NRoot& other)
    : Node{other}
{
}

// Move constructor
inline
NRoot::NRoot(NRoot&& other)
    : Node{std::move(other)}
{
}

// Destructor
inline
NRoot::~NRoot()
{
}

// Assignment operator
inline NRoot&
NRoot::operator=(const NRoot& other) {
    Node::operator=(other);
    return *this;
}

// Move assignment operator
inline NRoot&
NRoot::operator=(NRoot&& other) {
    Node::operator=(std::move(other));
    return *this;
}
/* }}} */

inline Visitor&
NRoot::traverse(Visitor& visitor) const {
    // TODO: Implement me!

    return visitor;
}

#endif /* end of include guard */
