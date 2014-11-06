#pragma once

#include <stdlib.h>
#include "vmips.h"
#define NUM_REGISTERS 32

typedef struct {
    Word32_t regs[NUM_REGISTERS];
    unsigned int num_regs;
    unsigned int reg_size;
} Reg_file_t; // mips has 32 registers, each holding a 32 bit word

Arch_info_t *arch_init() {
    return NULL;
}


#define REGISTER_WORD_SIZE 32

Reg_file_t *init_reg_file() {
    Reg_file_t *regs = malloc(sizeof *regs);
    regs->reg_size = REGISTER_WORD_SIZE;
    return regs;
}


#define MEM_SIZE_IN_WORDS 1000
#define MEM_WORD_SIZE 32

typedef struct {
    Word32_t memory[MEM_SIZE_IN_WORDS];
    unsigned int mem_words;
    unsigned int word_size;
} Memory_t;

Memory_t *init_memory_space() {
    Memory_t *mem = malloc(sizeof *mem);
    mem->mem_words = MEM_SIZE_IN_WORDS;
    mem->word_size = MEM_WORD_SIZE;
    return mem;
}
