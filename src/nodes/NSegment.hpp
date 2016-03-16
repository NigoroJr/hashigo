#ifndef NSEGMENT_HPP_
#define NSEGMENT_HPP_

#include "NBlockish.hpp"

struct NSegment : public NBlockish {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NSegment();

    NSegment(const NBlockish* b, const unsigned rung_count);

    // Copy constructor
    NSegment(const NSegment& other);

    // Move constructor
    NSegment(NSegment&& other);

    // Destructor
    ~NSegment();

    // Assignment operator
    NSegment&
    operator=(const NSegment& other);

    // Move assignment operator
    NSegment&
    operator=(NSegment&& other);
    /* }}} */

    NBlockish* block;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NSegment::NSegment()
    : NBlockish{0}
    , block{nullptr}
{
}

inline
NSegment::NSegment(const NBlockish* b, const unsigned rung_count)
    : NBlockish{rung_count}
    , block{const_cast<NBlockish*>(b)}
{
}

// Copy constructor
inline
NSegment::NSegment(const NSegment& other)
    : NBlockish{other}
    , block{other.block}
{
}

// Move constructor
inline
NSegment::NSegment(NSegment&& other)
    : NBlockish{std::move(other)}
    , block{std::move(other.block)}
{
}

// Destructor
inline
NSegment::~NSegment()
{
}

// Assignment operator
inline NSegment&
NSegment::operator=(const NSegment& other) {
    NBlockish::operator=(other);
    block = other.block;
    return *this;
}

// Move assignment operator
inline NSegment&
NSegment::operator=(NSegment&& other) {
    NBlockish::operator=(std::move(other));
    block = std::move(other.block);
    return *this;
}
/* }}} */

#endif /* end of include guard */
