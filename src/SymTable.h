#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include <cctype>
#include <unordered_map>
#include <unordered_set>

class SymTable {
public:
    /* Whether (in Verilog) it's a reg or wire */
    enum PinType {
        REG, WIRE,
    };

    /* Address is used as input, output, or both */
    enum IOType {
        IN, OUT, INOUT,
    };

    /**
     * Symbol table entry.
     */
    struct Entry {
        /* Name of the address in the Verilog source code */
        std::string var_name;

        /* Width of address (in Verilog code) in bits */
        unsigned width;

        /* reg or wire */
        PinType pin_type;

        /* Input, output, or both */
        IOType io_type;

        /* Which rung(s) the address appears in */
        std::unordered_set<unsigned> rungs;
    };

    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    SymTable();

    // Copy constructor
    SymTable(const SymTable& other);

    // Move constructor
    SymTable(SymTable&& other);

    // Destructor
    ~SymTable();

    // Assignment operator
    SymTable&
    operator=(const SymTable& other);

    // Move assignment operator
    SymTable&
    operator=(SymTable&& other);
    /* }}} */

private:
    /**
     * Normalizes the address name so that it can is a valid Verilog variable
     * name.
     * Converts all [^a-zA-Z0-9_] (i.e. non-alphanumeric) to '_'.
     */
    std::string
    normalize_name(const std::string& orig);

    std::unordered_map<std::string, SymTable::Entry> symtable;
};

#endif /* end of include guard */
