#ifndef NINSTRUCTION_HPP_
#define NINSTRUCTION_HPP_

#include <string>

#include "Node.hpp"

struct NInstruction : public Node {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NInstruction();

    NInstruction(const std::string& name, const unsigned rung_count);

    // Copy constructor
    NInstruction(const NInstruction& other);

    // Move constructor
    NInstruction(NInstruction&& other);

    // Destructor
    ~NInstruction();

    // Assignment operator
    NInstruction&
    operator=(const NInstruction& other);

    // Move assignment operator
    NInstruction&
    operator=(NInstruction&& other);
    /* }}} */

    std::string name;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NInstruction::NInstruction()
    : Node{0}
    , name{}
{ }

inline
NInstruction::NInstruction(const std::string& name, const unsigned rung_count)
    : Node{rung_count}
    , name{name}
{ }

// Copy constructor
inline
NInstruction::NInstruction(const NInstruction& other)
    : Node{other}
    , name{other.name}
{ }

// Move constructor
inline
NInstruction::NInstruction(NInstruction&& other)
    : Node{std::move(other)}
    , name{std::move(other.name)}
{ }

// Destructor
inline
NInstruction::~NInstruction()
{ }

// Assignment operator
inline NInstruction&
NInstruction::operator=(const NInstruction& other) {
    Node::operator=(other);
    name = other.name;
    return *this;
}

// Move assignment operator
inline NInstruction&
NInstruction::operator=(NInstruction&& other) {
    Node::operator=(std::move(other));
    name = std::move(other.name);
    return *this;
}
/* }}} */

#endif /* end of include guard */
