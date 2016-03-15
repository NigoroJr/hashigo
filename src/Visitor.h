#ifndef VISITOR_H_
#define VISITOR_H_

#include "Outputter.h"
#include "SymTable.h"

class Visitor {
public:
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    Visitor();

    /**
     * \param[in] outputter the outputter to use to write the Verilog source
     */
    Visitor(const Outputter& outputter);

    // Copy constructor
    Visitor(const Visitor& other);

    // Move constructor
    Visitor(Visitor&& other);

    // Destructor
    ~Visitor();

    // Assignment operator
    Visitor&
    operator=(const Visitor& other);

    // Move assignment operator
    Visitor&
    operator=(Visitor&& other);
    /* }}} */

private:
    SymTable symtable;
    Outputter outputter;
};

#endif /* end of include guard */
