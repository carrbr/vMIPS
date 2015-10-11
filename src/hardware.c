#include <stdlib.h> 
#include "hardware.h" 
#include "instrs.h" 

void init_processor(Process_t *proc);

Reg_file_t *init_reg_file() {
    Reg_file_t *regs = malloc(sizeof *regs);
    if (regs == NULL) {
        ERR_PRINT("reg_file memory alloc failed\n");
    } else {
        regs->reg_size = REGISTER_WORD_SIZE;
        regs->num_regs = NUM_REGISTERS;
        regs->regs[0] = 0; // this reg is always $zero in real MIPS
    }
    return regs;
}

Memory_t *init_memory_space() {
    Memory_t *mem = malloc(sizeof *mem);
    mem->mem_words = MEM_SIZE_IN_WORDS;
    mem->word_size = MEM_WORD_SIZE;
    mem->word_size_bytes = MEM_WORD_SIZE / 8;
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

Process_t *build_process() {    
    // setup environment for code execution
    Process_t *proc = malloc(sizeof(Process_t));
    proc->reg_file = init_reg_file();
    proc->mem_space = init_memory_space();
    proc->terminate = FALSE; // obviously do not want to terminate immediately
    
    init_processor(proc);
    
    return proc;
}

void init_processor(Process_t *proc) {
    proc->reg_file->status = 0;
    proc->reg_file->pc = START_ADDR;
    proc->reg_file->regs[sp_REG] = proc->mem_space->word_size - 1; // start stack at top of mem space
    proc->reg_file->regs[fp_REG] = proc->reg_file->regs[sp_REG]; 
}

void cleanup(Arch_info_t *arch, Process_t *proc) {
    if (arch != NULL) {
        if (arch->opcode_table != NULL) free(arch->opcode_table);
        free(arch);
    }
    if (proc != NULL) {
        if (proc->mem_space != NULL) free(proc->mem_space);
        if (proc->reg_file != NULL) {
            free(proc->reg_file);
        }
        free(proc);
    }
}