#include "Inst2Verilog.h"

using addresses_t = Inst2Verilog::addresses_t;

const std::unordered_map<
    std::string,
    std::function<std::string(addresses_t, SymTable)>
> Inst2Verilog::INST_FUNC_MAP = {
    {"EQU", Inst2Verilog::EQU},
    {"MOV", Inst2Verilog::MOV},
    {"ADD", Inst2Verilog::ADD},
    {"OTE", Inst2Verilog::OTE},
    {"XIO", Inst2Verilog::XIO},
};


/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
Inst2Verilog::Inst2Verilog()
    : inst_name{}
{
}

Inst2Verilog::Inst2Verilog(const NInstruction* inst)
    : inst_name{inst->name}
{
}

Inst2Verilog::Inst2Verilog(const NInstruction& inst)
    : inst_name{inst.name}
{
}

Inst2Verilog::Inst2Verilog(const std::string& name)
    : inst_name{name}
{
}

// Copy constructor
Inst2Verilog::Inst2Verilog(const Inst2Verilog& other)
    : inst_name{other.inst_name}
{
}

// Move constructor
Inst2Verilog::Inst2Verilog(Inst2Verilog&& other)
    : inst_name{std::move(other.inst_name)}
{
}

// Destructor
Inst2Verilog::~Inst2Verilog()
{
}

// Assignment operator
Inst2Verilog&
Inst2Verilog::operator=(const Inst2Verilog& other) {
    inst_name = other.inst_name;
    return *this;
}

// Move assignment operator
Inst2Verilog&
Inst2Verilog::operator=(Inst2Verilog&& other) {
    inst_name = std::move(other.inst_name);
    return *this;
}
/* }}} */

std::string
Inst2Verilog::operator()(const addresses_t& addresses,
                         const SymTable& symtable) const {
    if (INST_FUNC_MAP.count(inst_name) == 0) {
        if (addresses.size() == 1) {
            return symtable[addresses.front()].var_name;
        }
        else {
            // Probably not a good thing to come here.
            // If there is a block like FOO(addr1, addr2) then there probably
            // should be a specific function (named FOO) to handle that.
            return "";
        }
    }

    return INST_FUNC_MAP.at(inst_name)(addresses, symtable);
}

std::string
Inst2Verilog::EQU(const addresses_t& addresses, const SymTable& symtable) {
    const auto& op1 = symtable[addresses[0]].var_name;
    const auto& op2 = symtable[addresses[1]].var_name;
    return "(" + op1 + " == " + op2 + ")";
}

std::string
Inst2Verilog::MOV(const addresses_t& addresses, const SymTable& symtable) {
    const auto& i = symtable[addresses[0]].var_name;
    const auto& o = symtable[addresses[1]].var_name;
    return "n_" + o + " <= " + i;
}

std::string
Inst2Verilog::ADD(const addresses_t& addresses, const SymTable& symtable) {
    const auto& o = symtable[addresses[0]].var_name;
    const auto& i1 = symtable[addresses[1]].var_name;
    const auto& i2 = symtable[addresses[2]].var_name;
    return "n_" + o + " <= " + i1 + " + " + i2;
}

std::string
Inst2Verilog::OTE(const addresses_t& addresses, const SymTable& symtable) {
    const auto& o = symtable[addresses[0]].var_name;
    // TODO: SymTable::Entry::{next,wire,next_wire}
    return "n_" + o;
}

std::string
Inst2Verilog::XIO(const addresses_t& addresses, const SymTable& symtable) {
    const auto& o = symtable[addresses[0]].var_name;
    return "!" + o;
}
