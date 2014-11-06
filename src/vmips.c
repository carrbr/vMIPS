#include <stdio.h>
#include "vmips.h"
#include "process.h"
#include "hardware.h"

int main() {
    init(); // TODO: this doesn't actually do anything yet

    Process_t *proc = build_process();

    // just perform some tests to make sure everything is working properly

    // iterate through reg file
    int i;
    for (i = 0; i < proc->reg_file->num_regs; i++) {
        proc->reg_file->regs[i] = i + 1;
    }

    for (i = 0; i < proc->reg_file->num_regs; i++) {
        printf("Reg[%d]: %d\n", i, proc->reg_file->regs[i]);
    }

    // iterate through reg file
    for (i = 0; i < proc->mem_space->mem_words; i++) {
        proc->mem_space->memory[i] = i + 1;
    }

    for (i = 0; i < proc->mem_space->mem_words; i++) {
        printf("Memory[%d]: %d\n", i, proc->mem_space->memory[i]);
    }

    Word32_t instr = 0b11110011011011101001001110010000;
    Word32_t mask = 0x07c00000;
    printf("Register for instr 11110011 01101110 10010011 10010000: %d\n", proc->reg_file->regs[(instr & mask) >> 22]);

}

Arch_info_t *init() {
    // get info from implementation about the architecture we are simulating
    Arch_info_t *arch_config = (Arch_info_t *)arch_init();
    return arch_config;
}

Process_t *build_process() {    
    // setup environment for code execution
    Process_t *proc = malloc(sizeof(Process_t));
    proc->reg_file = init_reg_file();
    proc->mem_space = init_memory_space();
    return proc;
}
