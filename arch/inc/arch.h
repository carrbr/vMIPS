#pragma once

#include "vmips.h"

/*
   define register parameters here
 */
#define NUM_REGISTERS 32
#define REGISTER_WORD_SIZE 32

/*
   define memory parameters here
 */
#define MEM_SIZE_IN_WORDS 1000
#define MEM_WORD_SIZE 32

/*
 * define processor's endian-ness
 */
#define ENDIANNESS VMIPS_LITTLE_ENDIAN

/*
 * define the processor's word size
 */
#define WORD_SIZE THIRTY_TWO_BIT
#define INSTR_LENGTH THIRTY_TWO_BIT

/*
 * define number of processor opcodes available
 */
#define OPCODE_COUNT 0x2C
