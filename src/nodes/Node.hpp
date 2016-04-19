#ifndef NODE_HPP_
#define NODE_HPP_

#include "SymTable.h"
#include "Outputter.h"

#include <stdexcept>
#include <utility>
#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * Base class for all the nodes in the Abstract Syntax Tree.
 */
struct Node {
    /**
     * Set of instructions that are outputs.
     * Key: instruction name (e.g. MOV)
     * Val: 0-based indices of the address that are outputs (e.g. 1)
     */
    const std::unordered_map<
        std::string,
        std::unordered_set<unsigned>
    > OUTPUT_INSTS = {
        {"ADD", {2}},
        {"MOV", {1}},
        {"OTE", {0}},
        {"TOF", {5}},   // The .DN address
        {"TON", {5}},   // The .DN address
    };

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

    virtual SymTable&
    populate_symtable(SymTable& symtable) const;

    /**
     * Returns the Verilog snippet of the Node.
     *
     * Outputter is passed in to this method because NRung and NRoot are the
     * only two nodes that require Outputter..
     */
    virtual std::string
    to_verilog(const SymTable& symtable) const;

    /**
     * Returns or modifies the Outputter to append the dot language for
     * GraphViz.
     */
    virtual std::string
    to_dot(Outputter& outputter, const SymTable& symtable) const;

    unsigned rung_count;

protected:
    /**
     * Suppresses the compiler's unused variable warnings.
     */
    template<typename T>
    void
    ignore_unused_warnings(const T&) const;
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

inline SymTable&
Node::populate_symtable(SymTable& symtable) const {
    throw std::runtime_error{"Sorry, unimplemented"};

    ignore_unused_warnings(symtable);
}

inline std::string
Node::to_verilog(const SymTable& symtable) const {
    throw std::runtime_error{"Sorry, unimplemented"};

    ignore_unused_warnings(symtable);
}

inline std::string
Node::to_dot(Outputter& outputter, const SymTable& symtable) const {
    throw std::runtime_error{"Sorry, unimplemented"};

    ignore_unused_warnings(outputter);
    ignore_unused_warnings(symtable);
}

template<typename T>
inline void
Node::ignore_unused_warnings(const T&) const {
    // Do nothing. Just shuts up the compiler
}

#endif /* end of include guard */
