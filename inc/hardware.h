#pragma once

#include <stdlib.h>
#include "vmips.h"
// this is user-defined architecture configuration parameters
#include "arch.h"


/*
   abstraction of the processor's register file (which will be kept separate from
   that of other processes
 */
typedef struct {
    Word32_t regs[NUM_REGISTERS];
    Word32_t pc; // program counter reg
    Word32_t status; // processor status reg
    Word32_t hi;
    Word32_t lo;
    unsigned int num_regs;
    unsigned int reg_size;
} Reg_file_t; // mips has 32 registers, each holding a 32 bit word

/*
   gets a pointer to a ready-to-use register file
 */
Reg_file_t *init_reg_file();
    
/*
   abstraction of a process' memory space
 */
typedef struct {
    Word32_t memory[MEM_SIZE_IN_WORDS];
    unsigned int mem_words;
    unsigned int word_size;
} Memory_t;

/*
   gets a pointer to a ready-to-use memory space
 */
Memory_t *init_memory_space();

typedef struct {
    Reg_file_t *reg_file;
    Memory_t *mem_space;
} Process_t;

Process_t *build_process();

/*
 * abstraction of processors opcode handling functions.
 *
 * This is a table of function pointers indexed by opcode
 */
typedef struct {
    void (*opcodes[OPCODE_COUNT]) (Decoded_instr_t, Process_t *);
    unsigned int num_opcodes;
} Opcode_table_t;

/*
 * contains information about the processor architecture
 */
typedef struct {
    int endian;
    int word_size;
    int instr_length;
    Opcode_table_t *opcode_table;
} Arch_info_t;

/*
TODO: implement this
should return a struct with info about the platform, including at least endian-ness
 */
Arch_info_t *arch_init();