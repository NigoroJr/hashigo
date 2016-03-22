#ifndef NPARALLEL_HPP_
#define NPARALLEL_HPP_

#include "NBlockish.hpp"
#include "SymTable.h"

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

    virtual SymTable&
    populate_symtable(SymTable& symtable) const override;

    std::vector<NBlockish*> blocks;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NParallel::NParallel()
    : NBlockish{0}
    , blocks{std::vector<NBlockish*>{}}
{
}

inline
NParallel::NParallel(const unsigned rung_count)
    : NBlockish{rung_count}
    , blocks{std::vector<NBlockish*>{}}
{
}

// Copy constructor
inline
NParallel::NParallel(const NParallel& other)
    : NBlockish{other}
    , blocks{other.blocks}
{
}

// Move constructor
inline
NParallel::NParallel(NParallel&& other)
     : NBlockish{std::move(other)}
     , blocks{std::move(other.blocks)}
{
}

// Destructor
inline
NParallel::~NParallel()
{
}

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

inline SymTable&
NParallel::populate_symtable(SymTable& symtable) const {
    for (auto& block : blocks) {
        block->populate_symtable(symtable);
    }
    return symtable;
}

#endif /* end of include guard */
