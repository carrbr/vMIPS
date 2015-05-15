#pragma once

#include "hardware.h"


Opcode_table_t *init_opcode_table();
void init_alu_func_table();

#define OPCODE_LENGTH 6

// special register indexes
#define v0_REG 2 // used for syscall identification
#define sp_REG 29 // stack pointer
#define fp_REG 30 // frame pointer

/*
 * Opcode Enums
 */
#define ALU 	0x00
#define J		0x02
#define JAL		0x03
#define BEQ		0x04
#define BNE		0x05
#define ADDI	0x08
#define ADDIU	0x09
#define SLTI	0x0A
#define SLTIU	0x0B
#define ANDI	0x0C
#define ORI		0x0D
#define LUI		0x0F
#define MFC0	0x10
#define LW		0x23
#define LBU		0x24
#define LHU		0x25
#define SB		0x28
#define SH		0x029
#define SW		0x2B

/*
 * start mips opcode handler function prototypes here
 */
void alu_op(Decoded_instr_t instr, Process_t *proc);

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
