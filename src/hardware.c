#include <stdlib.h>
#include "hardware.h"
#include "instrs.h"

Reg_file_t *init_reg_file() {
    Reg_file_t *regs = malloc(sizeof *regs);
    regs->reg_size = REGISTER_WORD_SIZE;
    regs->num_regs = NUM_REGISTERS;
    return regs;
}

Memory_t *init_memory_space() {
    Memory_t *mem = malloc(sizeof *mem);
    mem->mem_words = MEM_SIZE_IN_WORDS;
    mem->word_size = MEM_WORD_SIZE;
    return mem;
}

Arch_info_t *arch_init() {
    Arch_info_t *arch = malloc(sizeof *arch);
    arch->endian = ENDIANNESS;
    arch->word_size = WORD_SIZE;
    arch->instr_length = INSTR_LENGTH;
    arch->opcode_table = init_opcode_table();
    return arch;
}
