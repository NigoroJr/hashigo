#include "SymTable.h"

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
SymTable::SymTable()
    : symtable{}
{
}

// Copy constructor
SymTable::SymTable(const SymTable& other)
    : symtable{other.symtable}
{
}

// Move constructor
SymTable::SymTable(SymTable&& other)
    : symtable{std::move(other.symtable)}
{
}

// Destructor
SymTable::~SymTable()
{
}

// Assignment operator
SymTable&
SymTable::operator=(const SymTable& other) {
    symtable = other.symtable;
    return *this;
}

// Move assignment operator
SymTable&
SymTable::operator=(SymTable&& other) {
    symtable = std::move(other.symtable);
    return *this;
}
/* }}} */

std::string
SymTable::normalize_name(const std::string& orig) {
    std::string ret{orig};

    for (auto& c : ret) {
        if (!std::isalnum(c) && c != '_') {
            c = '_';
        }
    }

    return ret;
}
