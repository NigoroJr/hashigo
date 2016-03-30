#ifndef BLOCK2VERILOG_H_
#define BLOCK2VERILOG_H_

#include "nodes/NBlock.hpp"
#include "nodes/NBlockish.hpp"
#include "SymTable.h"

#include <functional>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

/**
 * Converts a block to Verilog code.
 */

class Block2Verilog {
public:
    using inputs_t = NBlockish*;
    using output_t = NBlock*;

    static const std::unordered_map<
        std::string,
        std::function<std::string(inputs_t, output_t, SymTable)>
    > INST_FUNC_MAP;

    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    Block2Verilog();

    Block2Verilog(const NInstruction* inst);

    Block2Verilog(const NInstruction& inst);

    Block2Verilog(const std::string& name);

    // Copy constructor
    Block2Verilog(const Block2Verilog& other);

    // Move constructor
    Block2Verilog(Block2Verilog&& other);

    // Destructor
    ~Block2Verilog();

    // Assignment operator
    Block2Verilog&
    operator=(const Block2Verilog& other);

    // Move assignment operator
    Block2Verilog&
    operator=(Block2Verilog&& other);
    /* }}} */

    std::string
    operator()(const inputs_t& inputs,
               const output_t& output,
               const SymTable& symtable) const;

    static
    std::string
    MOV(const inputs_t& inputs, const output_t& output, const SymTable& symtable);

    static
    std::string
    OTE(const inputs_t& inputs, const output_t& output, const SymTable& symtable);

    static
    std::string
    ADD(const inputs_t& inputs, const output_t& output, const SymTable& symtable);

    static
    std::string
    TON(const inputs_t& inputs, const output_t& output, const SymTable& symtable);

private:
    /**
     * Constructs the Verilog code in the form:
     *
     *     if (inputs->to_verilog) begin
     *         output->to_verilog();
     *     end
     */
    static
    std::string
    if_stmt_assign_to_output(const inputs_t& inputs,
                             const output_t& output,
                             const SymTable& symtable);

    std::string inst_name;
};

#endif /* end of include guard */
