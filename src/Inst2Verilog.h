#ifndef INST2VERILOG_H_
#define INST2VERILOG_H_

#include "nodes/NInstruction.hpp"
#include "nodes/NAddress.hpp"
#include "SymTable.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * A class to convert Ladder Logic instructions to Verilog snippets.
 *
 * This class can be used in two ways:
 *
 * 1. Inst2Verilog::MOV(addresses)
 *
 * 2. Inst2Verilog("MOV")(addresses)
 *
 * addresses is a vector of pointers to NAddress, which is how addresses are
 * stored in NBlock nodes. The latter usage is useful when the instruction
 * name is unknown. NInstruction instances can be passed in (rather than
 * std::string) like: Inst2Verilog(inst)(addresses).
 */

class Inst2Verilog {
public:
    using addresses_t = std::vector<NAddress*>;

    static const std::unordered_map<
        std::string,
        std::function<std::string(addresses_t, SymTable)>
    > INST_FUNC_MAP;

    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    Inst2Verilog();

    Inst2Verilog(const NInstruction* inst);

    Inst2Verilog(const NInstruction& inst);

    Inst2Verilog(const std::string& name);

    // Copy constructor
    Inst2Verilog(const Inst2Verilog& other);

    // Move constructor
    Inst2Verilog(Inst2Verilog&& other);

    // Destructor
    ~Inst2Verilog();

    // Assignment operator
    Inst2Verilog&
    operator=(const Inst2Verilog& other);

    // Move assignment operator
    Inst2Verilog&
    operator=(Inst2Verilog&& other);
    /* }}} */

    std::string
    operator()(const addresses_t& addresses, const SymTable& symtable) const;

    /* Instruction to Verilog snippet conversions */

    static
    std::string
    EQU(const addresses_t& addresses, const SymTable& symtable);

    /**
     * Assignment Verilog code (inside the if block).
     *
     * MOV(0, foo) becomes foo <= 0
     */
    static
    std::string
    MOV(const addresses_t& addresses, const SymTable& symtable);

    /**
     * Assignment part of ADD.
     *
     * ADD(1, foo, foo) becomes foo <= foo + 1
     */
    static
    std::string
    ADD(const addresses_t& addresses, const SymTable& symtable);

    static
    std::string
    OTE(const addresses_t& addresses, const SymTable& symtable);

    static
    std::string
    XIO(const addresses_t& addresses, const SymTable& symtable);

private:
    std::string inst_name;
};

#endif /* end of include guard */
