#pragma once

#include "hardware.h"


Opcode_table_t *init_opcode_table();

#define OPCODE_LENGTH 6

unsigned int get_opcode(Word32_t instr);


/*
 * start mips opcode handler function prototypes here
 */
void alu_op(Word32_t instr);
