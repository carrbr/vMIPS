#include <stdio.h>
#include "vmips.h"
#include "process.h"
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


    // try to use opcode table
    Arch_info_t *arch = arch_init();
    arch->opcode_table->opcodes[get_opcode(0x00000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x0B000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x0C000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x10000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x14000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x20000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x24000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x2B000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x2C000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x30000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x34000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x3C000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x40000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x8C000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x93000000)](1);
    arch->opcode_table->opcodes[get_opcode(0x94000000)](1);
    arch->opcode_table->opcodes[get_opcode(0xA3000000)](1);
    arch->opcode_table->opcodes[get_opcode(0xA4000000)](1);
    arch->opcode_table->opcodes[get_opcode(0xAC000000)](1);

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
