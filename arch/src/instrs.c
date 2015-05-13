#include <stdio.h>
#include "arch.h"
#include "instrs.h"
#include "debug.h"

/*
 * abstraction of ALU's function handling.
 *
 * This is a table of function pointers indexed by function code
 */
#define FUNC_CODE_COUNT 0x2F
static void (*funcs[FUNC_CODE_COUNT]) (Decoded_instr_t, Process_t *);


Opcode_table_t *init_opcode_table() {
    Opcode_table_t *opcodes = malloc(sizeof *opcodes);
    opcodes->num_opcodes = OPCODE_COUNT;
    opcodes->opcodes[ALU] = alu_op;
    
    init_alu_func_table();

    return opcodes;
}

void init_alu_func_table() {
    // implemented operations
    funcs[SLL] = alu_sll_op;
    funcs[SRL] = alu_srl_op;
    funcs[SRA] = alu_sra_op;
    funcs[SLLV] = alu_sllv_op;
    funcs[SRLV] = alu_srlv_op;
    funcs[JR] = alu_jr_op;
    funcs[SYSCALL] = alu_syscall_op;
    funcs[MFHI] = alu_mfhi_op;
    funcs[MFLO] = alu_mflo_op;
    funcs[MULT] = alu_mult_op;
    funcs[MULTU] = alu_multu_op;
    funcs[DIV] = alu_div_op;
    funcs[DIVU] = alu_divu_op;
    funcs[ADD] = alu_add_op;
    funcs[ADDU] = alu_addu_op;
    funcs[SUB] = alu_sub_op;
    funcs[SUBU] = alu_subu_op;
    funcs[AND] = alu_and_op;
    funcs[OR] = alu_or_op;
    funcs[XOR] = alu_xor_op;
    funcs[NOR] = alu_nor_op;
    funcs[SLT] = alu_slt_op;
    funcs[SLTU] = alu_sltu_op;
    
    /*
     * unimplemented operations
     *
     * we have empty slots in our table where MIPS has no ALU funcs
     * we are essentially trading space for lookup time
     */
    funcs[0x01] = alu_unimpl_op;
    funcs[0x05] = alu_unimpl_op;
    funcs[0x07] = alu_unimpl_op;
    funcs[0x09] = alu_unimpl_op;
    funcs[0x0A] = alu_unimpl_op;
    funcs[0x0B] = alu_unimpl_op;
    funcs[0x0D] = alu_unimpl_op;
    funcs[0x0E] = alu_unimpl_op;
    funcs[0x0F] = alu_unimpl_op;
    funcs[0x11] = alu_unimpl_op;
    funcs[0x13] = alu_unimpl_op;
    funcs[0x14] = alu_unimpl_op;
    funcs[0x15] = alu_unimpl_op;
    funcs[0x16] = alu_unimpl_op;
    funcs[0x17] = alu_unimpl_op;
    funcs[0x1C] = alu_unimpl_op;
    funcs[0x1D] = alu_unimpl_op;
    funcs[0x1E] = alu_unimpl_op;
    funcs[0x1F] = alu_unimpl_op;
    funcs[0x28] = alu_unimpl_op;
    funcs[0x29] = alu_unimpl_op;
    funcs[0x2C] = alu_unimpl_op;
    funcs[0x2D] = alu_unimpl_op;
    funcs[0x2E] = alu_unimpl_op;
    funcs[0x2F] = alu_unimpl_op;
}

void alu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("I'm an ALU OP\n");
    
    funcs[instr.instr.r.funct](instr, proc);
}

void alu_unimpl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("UNIMPLEMENTED OPERATION: CRASHING\n");
    exit(1);
}
void alu_sll_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("SLL FUNC");
}

void alu_srl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("SRL FUNC");
}

void alu_sra_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_sllv_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_srlv_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_jr_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_syscall_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_mfhi_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_mflo_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_mult_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_multu_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_div_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_divu_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_add_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_addu_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_sub_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_subu_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_and_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_or_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_xor_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_nor_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_slt_op(Decoded_instr_t instr, Process_t *proc) {
    
}

void alu_sltu_op(Decoded_instr_t instr, Process_t *proc) {
    
}