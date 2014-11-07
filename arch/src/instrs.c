#include <stdio.h>
#include "arch.h"
#include "instrs.h"

#define OPCODE_MASK 0xFC000000
#define OPCODE_SHIFT 26
Opcode_table_t *init_opcode_table() {
    Opcode_table_t *opcodes = malloc(sizeof *opcodes);
    opcodes->num_opcodes = OPCODE_COUNT;
    opcodes->opcodes[0] = alu_op;
    return opcodes;
}

unsigned int get_opcode(Word32_t instr) {
    return (OPCODE_MASK & instr) >> 26;
}

void alu_op(Word32_t instr) {
    printf("I'm an ALU OP\n");
}
