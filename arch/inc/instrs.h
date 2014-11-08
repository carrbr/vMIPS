#pragma once

#include "hardware.h"


Opcode_table_t *init_opcode_table();

#define OPCODE_LENGTH 6

unsigned int get_opcode(Word32_t instr);


/*
 * start mips opcode handler function prototypes here
 */
void alu_op_basic(Word32_t instr);
void jump_to_address(Word32_t instr);
void jump_and_link(Word32_t instr);
void branch_if_equal(Word32_t instr);
void branch_if_not_equal(Word32_t instr);
void add_immediate(Word32_t instr);
void add_unsigned_immediate(Word32_t instr);
void slti(Word32_t instr);
void sltiu(Word32_t instr);
void bitwise_and_immediate(Word32_t instr);
void bitwise_or_immediate(Word32_t instr);
void load_upper_immediate(Word32_t instr);
void mfc0(Word32_t instr);
void load_word(Word32_t instr);
void load_byte_unsigned(Word32_t instr);
void load_halfword_unsigned(Word32_t instr);
void store_byte(Word32_t instr);
void store_halfword(Word32_t instr);
void store_word(Word32_t instr);

