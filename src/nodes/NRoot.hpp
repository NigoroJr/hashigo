#ifndef NROOT_HPP_
#define NROOT_HPP_

#include "Node.hpp"
#include "NRung.hpp"
#include "SymTable.h"
#include "Outputter.h"

#include <cstdio>
#include <string>
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

    virtual SymTable&
    populate_symtable(SymTable& symtable) const override;

    void
    to_verilog(Outputter& outputter, const SymTable& symtable) const;

    virtual std::string
    to_dot(Outputter& outputter, const SymTable& symtable) const override;

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

inline SymTable&
NRoot::populate_symtable(SymTable& symtable) const {
    for (auto& rung : rungs) {
        rung->populate_symtable(symtable);
    }
    return symtable;
}

inline void
NRoot::to_verilog(Outputter& outputter, const SymTable& symtable) const {
    outputter.append("num_rungs", std::to_string(rungs.size()));

    char buf[512];
    for (auto& rung : rungs) {
        std::sprintf(buf, "%d: begin", rung->rung_count);
        outputter.append("rungs", buf);

        // Let the rung append its expression
        rung->to_verilog(outputter, symtable);

        outputter.append("rungs", "end");
    }

    for (const auto& p : symtable) {
        auto entry = p.second;

        if (std::isdigit(entry.var_name[0])) {
            // TODO: Create additional field in sym table indicating constant
            continue;
        }

        // Declare variables (both current and next (n_))
        if (entry.width == 1) {
            std::sprintf(buf,
                        "%s %s;\n%s n_%s;",
                        entry.pin_type_str().c_str(),
                        entry.var_name.c_str(),
                        entry.pin_type_str().c_str(),
                        entry.var_name.c_str());
        }
        else {
            std::sprintf(buf,
                        "%s [%d:0]%s;\n%s [%d:0]n_%s;",
                        entry.pin_type_str().c_str(),
                        entry.width - 1,
                        entry.var_name.c_str(),
                        entry.pin_type_str().c_str(),
                        entry.width - 1,
                        entry.var_name.c_str());
        }
        outputter.append("addresses", buf);

        // On reset
        std::sprintf(buf,
                     "%s <= %d'b0;",
                     entry.var_name.c_str(),
                     entry.width);
        outputter.append("reset_addresses", buf);

        // Update to new address
        std::sprintf(buf,
                     "%s <= n_%s;",
                     entry.var_name.c_str(),
                     entry.var_name.c_str());
        outputter.append("update_addresses", buf);
    }
}

inline std::string
NRoot::to_dot(Outputter& outputter, const SymTable& symtable) const {
    for (auto& rung : rungs) {
        rung->to_dot(outputter, symtable);
    }
    return "Sorry, unimplemented";
}

#endif /* end of include guard */
