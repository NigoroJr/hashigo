#include "Block2Verilog.h"

using inputs_t = Block2Verilog::inputs_t;
using output_t = Block2Verilog::output_t;

const std::unordered_map<
    std::string,
    std::function<std::string(inputs_t, output_t, SymTable)>
> Block2Verilog::INST_FUNC_MAP = {
    {"MOV", Block2Verilog::if_stmt_assign_to_output},
    {"OTE", Block2Verilog::OTE},
    {"ADD", Block2Verilog::if_stmt_assign_to_output},
    {"TON", Block2Verilog::TON},
};


/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
Block2Verilog::Block2Verilog()
    : inst_name{}
{
}

Block2Verilog::Block2Verilog(const NInstruction* inst)
    : inst_name{inst->name}
{
}

Block2Verilog::Block2Verilog(const NInstruction& inst)
    : inst_name{inst.name}
{
}

Block2Verilog::Block2Verilog(const std::string& name)
    : inst_name{name}
{
}

// Copy constructor
Block2Verilog::Block2Verilog(const Block2Verilog& other)
    : inst_name{other.inst_name}
{
}

// Move constructor
Block2Verilog::Block2Verilog(Block2Verilog&& other)
    : inst_name{std::move(other.inst_name)}
{
}

// Destructor
Block2Verilog::~Block2Verilog()
{
}

// Assignment operator
Block2Verilog&
Block2Verilog::operator=(const Block2Verilog& other) {
    inst_name = other.inst_name;
    return *this;
}

// Move assignment operator
Block2Verilog&
Block2Verilog::operator=(Block2Verilog&& other) {
    inst_name = std::move(other.inst_name);
    return *this;
}
/* }}} */

std::string
Block2Verilog::operator()(const inputs_t& inputs,
                          const output_t& output,
                          const SymTable& symtable) const {
    if (INST_FUNC_MAP.count(inst_name) == 0) {
        return "";
    }

    return INST_FUNC_MAP.at(inst_name)(inputs, output, symtable);
}

std::string
Block2Verilog::MOV(const inputs_t& inputs,
                   const output_t& output,
                   const SymTable& symtable) {
    return if_stmt_assign_to_output(inputs, output, symtable);
}

std::string
Block2Verilog::OTE(const inputs_t& inputs,
                   const output_t& output,
                   const SymTable& symtable) {
    std::ostringstream oss;
    oss << output->to_verilog(symtable);
    oss << " <= ";
    oss << inputs->to_verilog(symtable) << ";";
    return oss.str();
}

std::string
Block2Verilog::ADD(const inputs_t& inputs,
                   const output_t& output,
                   const SymTable& symtable) {
    std::ostringstream oss;
    oss << "if (" << inputs->to_verilog(symtable) << ") begin" << std::endl;
    oss << output->to_verilog(symtable) << ";" << std::endl;
    oss << "end";
    return oss.str();
}

std::string
Block2Verilog::TON(const inputs_t& inputs,
                   const output_t& output,
                   const SymTable& symtable) {
    std::ostringstream oss;

    const auto& addresses = output->addresses;
    const auto& en = symtable[addresses[3]].var_name;
    const auto& dn = symtable[addresses[5]].var_name;

    oss << "n_" << en << " <= ";
    oss << inputs->to_verilog(symtable) << ";" << std::endl;
    // Use wire from the Timer Verilog module
    oss << "n_" << dn << " <= " << dn << "_wire" << ";";

    return oss.str();
}

std::string
Block2Verilog::if_stmt_assign_to_output(const inputs_t& inputs,
                                        const output_t& output,
                                        const SymTable& symtable) {
    std::ostringstream oss;
    oss << "if (" << inputs->to_verilog(symtable) << ") begin" << std::endl;
    // Assignment (e.g. MOV(0, foo) becomes foo <= 8'd0)
    oss << output->to_verilog(symtable) << ";" << std::endl;
    oss << "end";
    return oss.str();
}
