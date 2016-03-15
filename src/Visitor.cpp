#include "Visitor.h"

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
Visitor::Visitor()
{ }

Visitor::Visitor(const Outputter& outputter)
    : symtable{}
    , outputter{outputter}
{ }

// Copy constructor
Visitor::Visitor(const Visitor& other)
    : symtable{other.symtable}
    , outputter{other.outputter}
{ }

// Move constructor
Visitor::Visitor(Visitor&& other)
    : symtable{std::move(other.symtable)}
    , outputter{std::move(other.outputter)}
{ }

// Destructor
Visitor::~Visitor()
{ }

// Assignment operator
Visitor&
Visitor::operator=(const Visitor& other) {
    symtable = other.symtable;
    outputter = other.outputter;
    return *this;
}

// Move assignment operator
Visitor&
Visitor::operator=(Visitor&& other) {
    symtable = std::move(other.symtable);
    outputter = std::move(other.outputter);
    return *this;
}
/* }}} */
