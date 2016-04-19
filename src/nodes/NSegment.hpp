#ifndef NSEGMENT_HPP_
#define NSEGMENT_HPP_

#include "NBlockish.hpp"
#include "SymTable.h"
#include "Outputter.h"

#include <string>
#include <sstream>

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

    virtual SymTable&
    populate_symtable(SymTable& symtable) const override;

    virtual std::string
    to_verilog(const SymTable& symtable) const override;

    virtual std::string
    to_dot(Outputter& outputter, const SymTable& symtable) const override;

    virtual bool
    is_output() const override;

    NBlockish* block;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
NSegment::NSegment()
    : NBlockish{NBlockish::BlockType::SEGMENT, 0}
    , block{nullptr}
{
}

inline
NSegment::NSegment(const NBlockish* b, const unsigned rung_count)
    : NBlockish{NBlockish::BlockType::SEGMENT, rung_count}
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

inline SymTable&
NSegment::populate_symtable(SymTable& symtable) const {
    return block->populate_symtable(symtable);
}

inline std::string
NSegment::to_verilog(const SymTable& symtable) const {
    std::ostringstream oss;
    oss << "("  << block->to_verilog(symtable) << ")" << std::flush;
    return oss.str();
}

inline std::string
NSegment::to_dot(Outputter& outputter, const SymTable& symtable) const {
    // TODO: Implement me!
    ignore_unused_warnings(outputter);
    ignore_unused_warnings(symtable);
    return "Sorry, unimplemented";
}

inline bool
NSegment::is_output() const {
    return block->is_output();
}

#endif /* end of include guard */
