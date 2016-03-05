#ifndef NPARALLEL_HPP_
#define NPARALLEL_HPP_

#include "NBlockish.hpp"

#include <vector>

struct NParallel : public NBlockish {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    NParallel();

    NParallel(const unsigned rung_count);

    // Copy constructor
    NParallel(const NParallel& other);

    // Move constructor
    NParallel(NParallel&& other);

    // Destructor
    ~NParallel();

    // Assignment operator
    NParallel&
    operator=(const NParallel& other);

    // Move assignment operator
    NParallel&
    operator=(NParallel&& other);
    /* }}} */

    std::vector<NBlockish*> blocks;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NParallel::NParallel()
    : NBlockish{0}
    , blocks{std::vector<NBlockish*>{}}
{ }

inline
NParallel::NParallel(const unsigned rung_count)
    : NBlockish{rung_count}
    , blocks{std::vector<NBlockish*>{}}
{ }

// Copy constructor
inline
NParallel::NParallel(const NParallel& other)
    : NBlockish{other}
    , blocks{other.blocks}
{ }

// Move constructor
inline
NParallel::NParallel(NParallel&& other)
     : NBlockish{std::move(other)}
     , blocks{std::move(other.blocks)}
{ }

// Destructor
inline
NParallel::~NParallel()
{ }

// Assignment operator
inline NParallel&
NParallel::operator=(const NParallel& other) {
    NBlockish::operator=(other);
    blocks = other.blocks;
    return *this;
}

// Move assignment operator
inline NParallel&
NParallel::operator=(NParallel&& other) {
    NBlockish::operator=(std::move(other));
    blocks = std::move(other.blocks);
    return *this;
}
/* }}} */

#endif /* end of include guard */
