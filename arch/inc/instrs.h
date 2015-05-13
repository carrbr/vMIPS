#pragma once

#include "hardware.h"


Opcode_table_t *init_opcode_table();
void init_alu_func_table();

#define OPCODE_LENGTH 6

unsigned int get_opcode(Word32_t instr);


/*
 * start mips opcode handler function prototypes here
 */
void alu_op(Word32_t instr, Process_t *proc);


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
#define SLT 	0x2A
#define SLTU 	0x2B


/*
 * ALU function handler function prototypes
 */
void alu_unimpl_op(Word32_t instr, Process_t *proc);
void alu_sll_op(Word32_t instr, Process_t *proc);
void alu_srl_op(Word32_t instr, Process_t *proc);
void alu_sra_op(Word32_t instr, Process_t *proc);
void alu_sllv_op(Word32_t instr, Process_t *proc);
void alu_srlv_op(Word32_t instr, Process_t *proc);
void alu_jr_op(Word32_t instr, Process_t *proc);
void alu_syscall_op(Word32_t instr, Process_t *proc);
void alu_mfhi_op(Word32_t instr, Process_t *proc);
void alu_mflo_op(Word32_t instr, Process_t *proc);
void alu_mult_op(Word32_t instr, Process_t *proc);
void alu_multu_op(Word32_t instr, Process_t *proc);
void alu_div_op(Word32_t instr, Process_t *proc);
void alu_divu_op(Word32_t instr, Process_t *proc);
void alu_add_op(Word32_t instr, Process_t *proc);
void alu_addu_op(Word32_t instr, Process_t *proc);
void alu_sub_op(Word32_t instr, Process_t *proc);
void alu_subu_op(Word32_t instr, Process_t *proc);
void alu_and_op(Word32_t instr, Process_t *proc);
void alu_or_op(Word32_t instr, Process_t *proc);
void alu_xor_op(Word32_t instr, Process_t *proc);
void alu_slt_op(Word32_t instr, Process_t *proc);
void alu_sltu_op(Word32_t instr, Process_t *proc);
