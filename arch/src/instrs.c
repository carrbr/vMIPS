#include <stdio.h>
#include "vmips.h"
#include "arch.h"
#include "instrs.h"
#include "debug.h"


/*
 * Global Variable
 *
 * necessary so that the syscall routine can access it and determine if program
 * is terminating
 */
extern int terminate;

/*
 * abstraction of ALU's function handling.
 *
 * This is a table of function pointers indexed by function code
 */
#define FUNC_CODE_COUNT 0x2C
static void (*funcs[FUNC_CODE_COUNT]) (Decoded_instr_t, Process_t *);


Opcode_table_t *init_opcode_table() {
    Opcode_table_t *opcodes = malloc(sizeof *opcodes);
    opcodes->num_opcodes = OPCODE_COUNT;
    opcodes->opcodes[ALU_OP] = alu_op;
    opcodes->opcodes[J_OP] = j_op;
    opcodes->opcodes[JAL_OP] = jal_op;
    opcodes->opcodes[BEQ_OP] = beq_op;
    opcodes->opcodes[BNE_OP] = bne_op;
    opcodes->opcodes[ADDI_OP] = addi_op;
    opcodes->opcodes[ADDIU_OP] = addiu_op;
    opcodes->opcodes[SLTI_OP] = slti_op;
    opcodes->opcodes[SLTIU_OP] = sltiu_op;
    opcodes->opcodes[ANDI_OP] = andi_op;
    opcodes->opcodes[ORI_OP] = ori_op;
    opcodes->opcodes[LUI_OP] = lui_op;
    opcodes->opcodes[MFC0_OP] = mfc0_op;
    opcodes->opcodes[LW_OP] = lw_op;
    opcodes->opcodes[LBU_OP] = lbu_op;
    opcodes->opcodes[LHU_OP] = lhu_op;
    opcodes->opcodes[SB_OP] = sb_op;
    opcodes->opcodes[SH_OP] = sh_op;
    opcodes->opcodes[SW_OP] = sw_op;
    
    /*
     * unimplemented operations
     *
     * we have empty slots in our table where MIPS has no opcode funcs
     * we are essentially trading space for lookup time and simplicity
     */
    opcodes->opcodes[0x01] = unimpl_op;
    opcodes->opcodes[0x06] = unimpl_op;
    opcodes->opcodes[0x07] = unimpl_op;
    opcodes->opcodes[0x0E] = unimpl_op;
    opcodes->opcodes[0x11] = unimpl_op;
    opcodes->opcodes[0x12] = unimpl_op;
    opcodes->opcodes[0x13] = unimpl_op;
    opcodes->opcodes[0x14] = unimpl_op;
    opcodes->opcodes[0x15] = unimpl_op;
    opcodes->opcodes[0x16] = unimpl_op;
    opcodes->opcodes[0x17] = unimpl_op;
    opcodes->opcodes[0x18] = unimpl_op;
    opcodes->opcodes[0x19] = unimpl_op;
    opcodes->opcodes[0x1A] = unimpl_op;
    opcodes->opcodes[0x1B] = unimpl_op;
    opcodes->opcodes[0x1C] = unimpl_op;
    opcodes->opcodes[0x1D] = unimpl_op;
    opcodes->opcodes[0x1E] = unimpl_op;
    opcodes->opcodes[0x1F] = unimpl_op;
    opcodes->opcodes[0x20] = unimpl_op;
    opcodes->opcodes[0x21] = unimpl_op;
    opcodes->opcodes[0x22] = unimpl_op;
    opcodes->opcodes[0x26] = unimpl_op;
    opcodes->opcodes[0x27] = unimpl_op;
    opcodes->opcodes[0x2A] = unimpl_op;
    
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
     * we are essentially trading space for lookup time and simplicity
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
}

/*
 * Opcode handler implementations
 */
 
void alu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("ALU OP\n");
    
    funcs[instr.instr.r.funct](instr, proc);
}

void j_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void jal_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void beq_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void bne_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void addi_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void addiu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("ADDIU OP\n");
    // TODO add overflow checks
    print_decoded_instr(&instr);
    proc->reg_file->regs[instr.instr.i.rt] = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm;
}

void slti_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void sltiu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void andi_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void ori_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void lui_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void mfc0_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void lw_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void lbu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void lhu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void sb_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void sh_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void sw_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT(" OP\n");
}

void unimpl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("UNIMPLEMENT OPERATION: CRASHING\n");
    exit(1); // TODO fix so we clean up properly
}




/*
 * ALU function implementations
 */
void alu_sll_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("SLL FUNC\n");
}

void alu_srl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("SRL FUNC\n");
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
    DEBUG_PRINT("SYSCALL FUNC\n");
    if (proc->reg_file->regs[v0_REG] == 10) { // exit
        DEBUG_PRINT("Exit Syscall\n");
        terminate = TRUE;
    }
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
    DEBUG_PRINT("ADD FUNC\n");
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

void alu_unimpl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("UNIMPLEMENTED OPERATION: CRASHING\n");
    exit(1); // TODO fix so we clean up properly
}