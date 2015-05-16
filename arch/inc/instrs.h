#pragma once

#include "hardware.h"


Opcode_table_t *init_opcode_table();
void init_alu_func_table();

#define OPCODE_LENGTH 6

// special register indexes
#define v0_REG 2 // used for syscall identification
#define a0_REG 4
#define a1_REG 5
#define sp_REG 29 // stack pointer
#define fp_REG 30 // frame pointer

/*
 * Opcode Enums
 */
#define ALU_OP 		0x00
#define J_OP		0x02
#define JAL_OP		0x03
#define BEQ_OP		0x04
#define BNE_OP		0x05
#define ADDI_OP 	0x08
#define ADDIU_OP	0x09
#define SLTI_OP		0x0A
#define SLTIU_OP	0x0B
#define ANDI_OP		0x0C
#define ORI_OP		0x0D
#define LUI_OP		0x0F
#define MFC0_OP		0x10
#define LW_OP		0x23
#define LBU_OP		0x24
#define LHU_OP		0x25
#define SB_OP		0x28
#define SH_OP		0x29
#define SW_OP		0x2B

/*
 * mips opcode handler function prototypes
 */
void alu_op(Decoded_instr_t instr, Process_t *proc);
void j_op(Decoded_instr_t instr, Process_t *proc);
void jal_op(Decoded_instr_t instr, Process_t *proc);
void beq_op(Decoded_instr_t instr, Process_t *proc);
void bne_op(Decoded_instr_t instr, Process_t *proc);
void addi_op(Decoded_instr_t instr, Process_t *proc);
void addiu_op(Decoded_instr_t instr, Process_t *proc);
void slti_op(Decoded_instr_t instr, Process_t *proc);
void sltiu_op(Decoded_instr_t instr, Process_t *proc);
void andi_op(Decoded_instr_t instr, Process_t *proc);
void ori_op(Decoded_instr_t instr, Process_t *proc);
void lui_op(Decoded_instr_t instr, Process_t *proc);
void mfc0_op(Decoded_instr_t instr, Process_t *proc);
void lw_op(Decoded_instr_t instr, Process_t *proc);
void lbu_op(Decoded_instr_t instr, Process_t *proc);
void lhu_op(Decoded_instr_t instr, Process_t *proc);
void sb_op(Decoded_instr_t instr, Process_t *proc);
void sh_op(Decoded_instr_t instr, Process_t *proc);
void sw_op(Decoded_instr_t instr, Process_t *proc);
void unimpl_op(Decoded_instr_t instr, Process_t *proc);


/*
 * ALU Function Enums
 */
#define SLL 	0x00
#define SRL 	0x02
#define SRA 	0x03
#define SLLV 	0x04
#define SRLV 	0x06
#define JR	 	0x08
#define SYSCALL	0x0C
#define MFHI 	0x10
#define MFLO 	0x12
#define MULT 	0x18
#define MULTU 	0x19
#define DIV    	0x1A
#define DIVU 	0x1B
#define ADD 	0x20
#define ADDU 	0x21
#define SUB 	0x22
#define SUBU 	0x23
#define AND 	0x24
#define OR	 	0x25
#define XOR 	0x26
#define NOR 	0x27
#define SLT 	0x2A
#define SLTU 	0x2B


/*
 * ALU function handler function prototypes
 */
void alu_unimpl_op(Decoded_instr_t instr, Process_t *proc);
void alu_sll_op(Decoded_instr_t instr, Process_t *proc);
void alu_srl_op(Decoded_instr_t instr, Process_t *proc);
void alu_sra_op(Decoded_instr_t instr, Process_t *proc);
void alu_sllv_op(Decoded_instr_t instr, Process_t *proc);
void alu_srlv_op(Decoded_instr_t instr, Process_t *proc);
void alu_jr_op(Decoded_instr_t instr, Process_t *proc);
void alu_syscall_op(Decoded_instr_t instr, Process_t *proc);
void alu_mfhi_op(Decoded_instr_t instr, Process_t *proc);
void alu_mflo_op(Decoded_instr_t instr, Process_t *proc);
void alu_mult_op(Decoded_instr_t instr, Process_t *proc);
void alu_multu_op(Decoded_instr_t instr, Process_t *proc);
void alu_div_op(Decoded_instr_t instr, Process_t *proc);
void alu_divu_op(Decoded_instr_t instr, Process_t *proc);
void alu_add_op(Decoded_instr_t instr, Process_t *proc);
void alu_addu_op(Decoded_instr_t instr, Process_t *proc);
void alu_sub_op(Decoded_instr_t instr, Process_t *proc);
void alu_subu_op(Decoded_instr_t instr, Process_t *proc);
void alu_and_op(Decoded_instr_t instr, Process_t *proc);
void alu_or_op(Decoded_instr_t instr, Process_t *proc);
void alu_xor_op(Decoded_instr_t instr, Process_t *proc);
void alu_nor_op(Decoded_instr_t instr, Process_t *proc);
void alu_slt_op(Decoded_instr_t instr, Process_t *proc);
void alu_sltu_op(Decoded_instr_t instr, Process_t *proc);
