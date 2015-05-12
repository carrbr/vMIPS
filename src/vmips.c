#include <stdio.h>
#include "vmips.h"
#include "hardware.h"
#include "instrs.h"

int main() {

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

    // iterate through memory space
    for (i = 0; i < proc->mem_space->mem_words; i++) {
        proc->mem_space->memory[i] = i + 1;
    }

    for (i = 0; i < proc->mem_space->mem_words; i++) {
        printf("Memory[%d]: %d\n", i, proc->mem_space->memory[i]);
    }

    Word32_t instr = 0x036E9390; // 0b00000011 01101110 10010011 10010000
    Decoded_instr_t dinstr = decode_instr(instr); // TODO make sure we check for NOOPs
    printf("Register for instr 11110011 01101110 10010011 10010000: %d\n", proc->reg_file->regs[dinstr.instr.r.rt]);
    
    // try to use opcode table
    Arch_info_t *arch = arch_init();
    arch->opcode_table->opcodes[dinstr.opcode](dinstr, proc);
    
    instr = 0x0B6E9390; // 0b00001011 01101110 10010011 10010000
    dinstr = decode_instr(instr);
    
    instr = 0x436E9390; // 0b01000011 01101110 10010011 10010000
    dinstr = decode_instr(instr);

    // clean up after ourselves
    free(arch->opcode_table);
    free(arch);
    free(proc->mem_space);
    free(proc->reg_file);
    free(proc);
}

Process_t *build_process() {    
    // setup environment for code execution
    Process_t *proc = malloc(sizeof(Process_t));
    proc->reg_file = init_reg_file();
    proc->mem_space = init_memory_space();
    return proc;
}
