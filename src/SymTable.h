#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include <algorithm>
#include <cctype>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Prevent circular inclusion
struct NAddress;

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
        /* Constructors, Destructor, and Assignment operators {{{ */
        // Default constructor
        Entry();

        /**
         * Adds a Ladder Logic address to Verilog variable entry with the
         * given information.
         * Use the append method after instantiating this instance to add the
         * rung number.
         */
        Entry(const std::string& var_name,
              const unsigned width,
              const PinType& pin_type,
              const IOType& io_type);

        // Copy constructor
        Entry(const Entry& other);

        // Move constructor
        Entry(Entry&& other);

        // Destructor
        ~Entry();

        // Assignment operator
        Entry&
        operator=(const Entry& other);

        // Move assignment operator
        Entry&
        operator=(Entry&& other);
        /* }}} */

        /**
         * Appends another rung in which this entry is used.
         * If this address is currently an input and the given IOType is an
         * output (or vice versa), the io_type is changed to INOUT and the
         * PinType is changed to a reg, indicating that this is used in a
         * sequential logic.
         *
         * \param[in] rung the rung number that this address is used
         *
         * \param[in] io_type
         *
         * \return reference to the updated instance of the entry
         */
        // TODO: PinType => LogicType? But we can use reg for combinational
        void
        append(const unsigned rung, const IOType& io_type);

        std::string
        pin_type_str() const;

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


public:
    using symtable_t = std::unordered_map<std::string, SymTable::Entry>;
    using iterator = typename symtable_t::iterator;
    using const_iterator = typename symtable_t::const_iterator;

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

    Entry&
    operator[](const NAddress* address);

    Entry&
    operator[](const std::string& address);

    const Entry&
    operator[](const NAddress* address) const;

    const Entry&
    operator[](const std::string& address) const;

    /**
     * Checks whether the given address is present in the symbol table.
     */
    bool
    exists(const std::string& address) const;

    /* Iterators */

    const_iterator
    begin() const;

    const_iterator
    end() const;

    iterator
    begin();

    iterator
    end();

private:
    /**
     * Normalizes the address name so that it is a valid Verilog variable
     * name.
     * Converts all [^a-zA-Z0-9_] (i.e. non-alphanumeric) to '_'.
     */
    std::string
    normalize_name(const std::string& orig) const;

    symtable_t symtable;
};

using iterator = typename SymTable::iterator;
using const_iterator = typename SymTable::const_iterator;

inline const_iterator
SymTable::begin() const {
    return symtable.begin();
}

inline const_iterator
SymTable::end() const {
    return symtable.end();
}

inline iterator
SymTable::begin() {
    return symtable.begin();
}

inline iterator
SymTable::end() {
    return symtable.end();
}

#endif /* end of include guard */
