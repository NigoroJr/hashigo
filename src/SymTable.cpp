#include "SymTable.h"

#include "nodes/NAddress.hpp"

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
SymTable::Entry::Entry()
    : var_name{}
    , width{0}
    , pin_type{SymTable::PinType::REG}
    , io_type{SymTable::IOType::IN}
    , rungs{}
{
}

SymTable::Entry::Entry(const std::string& var_name,
                       const unsigned width,
                       const PinType& pin_type,
                       const IOType& io_type)
    : var_name{var_name}
    , width{width}
    , pin_type{pin_type}
    , io_type{io_type}
    , rungs{std::unordered_set<unsigned>{}}
{
}

// Copy constructor
SymTable::Entry::Entry(const SymTable::Entry& other)
    : var_name{other.var_name}
    , width{other.width}
    , pin_type{other.pin_type}
    , io_type{other.io_type}
    , rungs{other.rungs}
{
}

// Move constructor
SymTable::Entry::Entry(SymTable::Entry&& other)
    : var_name{std::move(other.var_name)}
    , width{std::move(other.width)}
    , pin_type{std::move(other.pin_type)}
    , io_type{std::move(other.io_type)}
    , rungs{std::move(other.rungs)}
{
}

// Destructor
SymTable::Entry::~Entry()
{
}

// Assignment operator
SymTable::Entry&
SymTable::Entry::operator=(const SymTable::Entry& other) {
    var_name = other.var_name;
    width = other.width;
    pin_type = other.pin_type;
    io_type = other.io_type;
    rungs = other.rungs;
    return *this;
}

// Move assignment operator
SymTable::Entry&
SymTable::Entry::operator=(SymTable::Entry&& other) {
    var_name = std::move(other.var_name);
    width = std::move(other.width);
    pin_type = std::move(other.pin_type);
    io_type = std::move(other.io_type);
    rungs = std::move(other.rungs);
    return *this;
}
/* }}} */

void
SymTable::Entry::append(const unsigned rung, const IOType& io_type) {
    rungs.insert(rung);

    if ((this->io_type == IOType::IN && io_type == IOType::OUT)
        || (this->io_type == IOType::OUT && io_type == IOType::IN)) {
        this->io_type = IOType::INOUT;
        // Need sequential logic
        this->pin_type = PinType::REG;
    }
}

std::string
SymTable::Entry::pin_type_str() const {
    return pin_type == PinType::WIRE ? "wire" : "reg";
}

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

SymTable::Entry&
SymTable::operator[](const NAddress* address) {
    return operator[](address->name);
}

SymTable::Entry&
SymTable::operator[](const std::string& address) {
    if (symtable.count(address) != 0) {
        return symtable[address];
    }

    // TODO: Are these default values ok?
    symtable[address] = SymTable::Entry{
        normalize_name(address),
        // TODO: adjust size
        32,
        SymTable::PinType::REG,
        SymTable::IOType::IN
    };
    return symtable[address];
}

const SymTable::Entry&
SymTable::operator[](const NAddress* address) const {
    return operator[](address->name);
}

const SymTable::Entry&
SymTable::operator[](const std::string& address) const {
    return symtable.at(address);
}

bool
SymTable::exists(const std::string& address) const {
    return symtable.find(address) != symtable.end();
}

std::string
SymTable::normalize_name(const std::string& orig) const {
    std::string ret{orig};

    for (auto& c : ret) {
        if (!std::isalnum(c) && c != '_') {
            c = '_';
        }
    }

    std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);

    return ret;
}
