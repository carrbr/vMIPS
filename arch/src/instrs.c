#include <stdio.h>
#include "arch.h"
#include "instrs.h"
#include "debug.h"

#define OPCODE_MASK 0xFC000000 // get the opcode
#define OPCODE_SHIFT 26
#define FUNC_MASK 0x0000003F // get the function code

/*
 * abstraction of ALU's function handling.
 *
 * This is a table of function pointers indexed by function code
 */
#define FUNC_CODE_COUNT 0x2F
static void (*funcs[FUNC_CODE_COUNT]) (Word32_t, Process_t *);


Opcode_table_t *init_opcode_table() {
    Opcode_table_t *opcodes = malloc(sizeof *opcodes);
    opcodes->num_opcodes = OPCODE_COUNT;
    opcodes->opcodes[0] = alu_op;
    
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
    funcs[0x27] = alu_unimpl_op;
    funcs[0x28] = alu_unimpl_op;
    funcs[0x29] = alu_unimpl_op;
    funcs[0x2C] = alu_unimpl_op;
    funcs[0x2D] = alu_unimpl_op;
    funcs[0x2E] = alu_unimpl_op;
    funcs[0x2F] = alu_unimpl_op;
}

unsigned int get_opcode(Word32_t instr) {
    return (OPCODE_MASK & instr) >> 26;
}

void alu_op(Word32_t instr, Process_t *proc) {
    DEBUG_PRINT("I'm an ALU OP\n");
    if (instr == 0) {
        // NOOP --> do nothing
        DEBUG_PRINT("NOOP\n");
        return;
    }
    printf("INSTR: %X\n", instr);
    
    Word32_t func_code = instr & FUNC_MASK;
    funcs[func_code](instr, proc);
}

void alu_unimpl_op(Word32_t instr, Process_t *proc) {
    DEBUG_PRINT("UNIMPLEMENTED OPERATION: CRASHING\n");
    exit(1);
}
void alu_sll_op(Word32_t instr, Process_t *proc) {
    
}

void alu_srl_op(Word32_t instr, Process_t *proc) {
    
}

void alu_sra_op(Word32_t instr, Process_t *proc) {
    
}

void alu_sllv_op(Word32_t instr, Process_t *proc) {
    
}

void alu_srlv_op(Word32_t instr, Process_t *proc) {
    
}

void alu_jr_op(Word32_t instr, Process_t *proc) {
    
}

void alu_syscall_op(Word32_t instr, Process_t *proc) {
    
}

void alu_mfhi_op(Word32_t instr, Process_t *proc) {
    
}

void alu_mflo_op(Word32_t instr, Process_t *proc) {
    
}

void alu_mult_op(Word32_t instr, Process_t *proc) {
    
}

void alu_multu_op(Word32_t instr, Process_t *proc) {
    
}

void alu_div_op(Word32_t instr, Process_t *proc) {
    
}

void alu_divu_op(Word32_t instr, Process_t *proc) {
    
}

void alu_add_op(Word32_t instr, Process_t *proc) {
    
}

void alu_addu_op(Word32_t instr, Process_t *proc) {
    
}

void alu_sub_op(Word32_t instr, Process_t *proc) {
    
}

void alu_subu_op(Word32_t instr, Process_t *proc) {
    
}

void alu_and_op(Word32_t instr, Process_t *proc) {
    
}

void alu_or_op(Word32_t instr, Process_t *proc) {
    
}

void alu_xor_op(Word32_t instr, Process_t *proc) {
    
}

void alu_slt_op(Word32_t instr, Process_t *proc) {
    
}

void alu_sltu_op(Word32_t instr, Process_t *proc) {
    
}