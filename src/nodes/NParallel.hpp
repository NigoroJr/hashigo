#ifndef NPARALLEL_HPP_
#define NPARALLEL_HPP_

#include "NBlockish.hpp"
#include "SymTable.h"
#include "Outputter.h"

#include <algorithm>
#include <string>
#include <sstream>
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

    virtual std::string
    to_verilog(const SymTable& symtable) const override;

    virtual std::string
    to_dot(Outputter& outputter, const SymTable& symtable) const override;

    virtual bool
    is_output() const override;

    std::vector<NBlockish*> blocks;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NParallel::NParallel()
    : NBlockish{NBlockish::BlockType::PARALLEL, 0}
    , blocks{std::vector<NBlockish*>{}}
{
}

inline
NParallel::NParallel(const unsigned rung_count)
    : NBlockish{NBlockish::BlockType::PARALLEL, rung_count}
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

inline std::string
NParallel::to_verilog(const SymTable& symtable) const {
    std::ostringstream oss;
    oss << "(";
    for (unsigned i = 0; i < blocks.size(); i++) {
        oss << blocks[i]->to_verilog(symtable);

        // Join with | because this is a parallel connection
        if (i != blocks.size() - 1) {
            oss << " | ";
        }
    }
    oss << ")" << std::flush;

    return oss.str();
}

inline std::string
NParallel::to_dot(Outputter& outputter, const SymTable& symtable) const {
    // TODO: Implement me!
    ignore_unused_warnings(outputter);
    ignore_unused_warnings(symtable);
    return "Sorry, unimplemented";
}

inline bool
NParallel::is_output() const {
    auto l = [](const NBlockish* b) {
        return b->is_output();
    };
    return std::all_of(blocks.begin(), blocks.end(), l);
}

#endif /* end of include guard */
