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
#define MEM_SIZE_IN_WORDS 0x4000
#define MEM_WORD_SIZE 32
#define MEM_WORD_SIZE_BYTES 4
#define START_ADDR 0x00000000 // address will first instruction to exec will be loaded

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

/*
 * Instruction Type Enums
 */
#define R_TYPE 0
#define I_TYPE 1
#define J_TYPE 2

/*
 * Instruction-type-specific info containers for each type
 */
typedef struct {
    unsigned short rs; // arg reg s
    unsigned short rt; // arg reg t
    unsigned short rd; // dest reg d
    unsigned short shamt; // shift amount
    unsigned short funct; // function code
} r_type_t;

typedef struct {
    unsigned short rs; // arg reg s
    unsigned short rt; // dest reg t
    unsigned short imm; // immediate value
} i_type_t;

typedef struct {
    unsigned int addr; // jump address
} j_type_t;

/*
 * contains decoded instr information
 */
typedef struct {
    unsigned short opcode;
    unsigned short instr_type;
    union info {
        r_type_t r;
        i_type_t i;
        j_type_t j;
    } instr;
} Decoded_instr_t;

Decoded_instr_t decode_instr(Word32_t instr);
void print_decoded_instr(const Decoded_instr_t *di);

/*
 * masks and offsets for decoding instructions
 */
#define OPCODE_MASK 0xFC000000
#define OPCODE_SHIFT 26

#define FUNCT_MASK 0x0000003F
#define FUNCT_WIDTH 6

#define SHAMT_AND_RX_MASK 0x0000001F
#define SHAMT_AND_RX_WIDTH 5

#define IMM_MASK 0x0000FFFF
#define IMM_WIDTH 16

#define ADDR_MASK 0x03FFFFFF
#define ADDR_WIDTH

/*
 * Some useful numerical constants
 */
const extern int32_t MAX_INT;
const extern uint32_t U_MAX_INT;
const extern int32_t MIN_INT;
const extern uint32_t U_MIN_INT;