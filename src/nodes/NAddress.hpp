#ifndef NADDRESS_HPP_
#define NADDRESS_HPP_

#include "Node.hpp"

#include <string>

struct NAddress : public Node {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NAddress();

    NAddress(const std::string& name, const unsigned rung_count);

    // Copy constructor
    NAddress(const NAddress& other);

    // Move constructor
    NAddress(NAddress&& other);

    // Destructor
    ~NAddress();

    // Assignment operator
    NAddress&
    operator=(const NAddress& other);

    // Move assignment operator
    NAddress&
    operator=(NAddress&& other);
    /* }}} */

    std::string name;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NAddress::NAddress()
    : Node{0}
    , name{}
{ }

inline
NAddress::NAddress(const std::string& name, const unsigned rung_count)
    : Node{rung_count}
    , name{name}
{ }

// Copy constructor
inline
NAddress::NAddress(const NAddress& other)
    : Node{other}
    , name{other.name}
{ }

// Move constructor
inline
NAddress::NAddress(NAddress&& other)
    : Node{other}
    , name{std::move(other.name)}
{ }

// Destructor
inline
NAddress::~NAddress()
{ }

// Assignment operator
inline NAddress&
NAddress::operator=(const NAddress& other) {
    Node::operator=(other);
    name = other.name;
    return *this;
}

// Move assignment operator
inline NAddress&
NAddress::operator=(NAddress&& other) {
    Node::operator=(std::move(other));
    name = std::move(other.name);
    return *this;
}
/* }}} */

#endif /* end of include guard */
