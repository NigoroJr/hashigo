#ifndef NRUNG_HPP_
#define NRUNG_HPP_

#include "Node.hpp"
#include "NBlockish.hpp"

#include <utility>

struct NRung : public Node {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NRung();

    NRung(const NBlockish* b, const unsigned rung_count);

    // Copy constructor
    NRung(const NRung& other);

    // Move constructor
    NRung(NRung&& other);

    // Destructor
    ~NRung();

    // Assignment operator
    NRung&
    operator=(const NRung& other);

    // Move assignment operator
    NRung&
    operator=(NRung&& other);
    /* }}} */

    NBlockish* block;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NRung::NRung()
    : Node{0}
    , block{nullptr}
{ }

inline
NRung::NRung(const NBlockish* b, const unsigned rung_count)
    : Node{rung_count}
    , block{const_cast<NBlockish*>(b)}
{ }

// Copy constructor
inline
NRung::NRung(const NRung& other)
    : Node{other}
    , block{other.block}
{ }

// Move constructor
inline
NRung::NRung(NRung&& other)
    : Node{std::move(other)}
    , block{std::move(other.block)}
{ }

// Destructor
inline
NRung::~NRung()
{ }

// Assignment operator
inline NRung&
NRung::operator=(const NRung& other) {
    Node::operator=(other);
    block = other.block;
    return *this;
}

// Move assignment operator
inline NRung&
NRung::operator=(NRung&& other) {
    Node::operator=(std::move(other));
    block = std::move(other.block);
    return *this;
}
/* }}} */

#endif /* end of include guard */
