#include <stdio.h>
#include "arch.h"
#include "instrs.h"

#define OPCODE_MASK 0xFC000000
#define OPCODE_SHIFT 26
Opcode_table_t *init_opcode_table() {
    Opcode_table_t *opcodes = malloc(sizeof *opcodes);
    opcodes->num_opcodes = OPCODE_COUNT;
    opcodes->opcodes[0x0] = alu_op_basic;
    opcodes->opcodes[0x2] = jump_to_address;
    opcodes->opcodes[0x3] = jump_and_link;
    opcodes->opcodes[0x4] = branch_if_equal;
    opcodes->opcodes[0x5] = branch_if_not_equal;
    opcodes->opcodes[0x8] = add_immediate;
    opcodes->opcodes[0x9] = add_unsigned_immediate;
    opcodes->opcodes[0xA] = slti;
    opcodes->opcodes[0xB] = sltiu;
    opcodes->opcodes[0xC] = bitwise_and_immediate;
    opcodes->opcodes[0xD] = bitwise_or_immediate;
    opcodes->opcodes[0xF] = load_upper_immediate;
    opcodes->opcodes[0x10] = mfc0;
    opcodes->opcodes[0x23] = load_word;
    opcodes->opcodes[0x24] = load_byte_unsigned;
    opcodes->opcodes[0x25] = load_halfword_unsigned;
    opcodes->opcodes[0x28] = store_byte;
    opcodes->opcodes[0x29] = store_halfword;
    opcodes->opcodes[0x2B] = store_word;

    return opcodes;
}

unsigned int get_opcode(Word32_t instr) {
    // printf("opcode: %x\n", (OPCODE_MASK & instr) >> OPCODE_SHIFT);
    return (OPCODE_MASK & instr) >> OPCODE_SHIFT;
}

void alu_op_basic(Word32_t instr) {
    printf("%s\n", __func__);
}

void jump_to_address(Word32_t instr) {
    printf("%s\n", __func__);
}

void jump_and_link(Word32_t instr) {
    printf("%s\n", __func__);
}

void branch_if_equal(Word32_t instr) {
    printf("%s\n", __func__);
}

void branch_if_not_equal(Word32_t instr) {
    printf("%s\n", __func__);
}

void add_immediate(Word32_t instr) {
    printf("%s\n", __func__);
}

void add_unsigned_immediate(Word32_t instr) {
    printf("%s\n", __func__);
}

void slti(Word32_t instr) {
    printf("%s\n", __func__);
}

void sltiu(Word32_t instr) {
    printf("%s\n", __func__);
}

void bitwise_and_immediate(Word32_t instr) {
    printf("%s\n", __func__);
}

void bitwise_or_immediate(Word32_t instr) {
    printf("%s\n", __func__);
}

void load_upper_immediate(Word32_t instr) {
    printf("%s\n", __func__);
}

void mfc0(Word32_t instr) {
    printf("%s\n", __func__);
}

void load_word(Word32_t instr) {
    printf("%s\n", __func__);
}

void load_byte_unsigned(Word32_t instr) {
    printf("%s\n", __func__);
}

void load_halfword_unsigned(Word32_t instr) {
    printf("%s\n", __func__);
}

void store_byte(Word32_t instr) {
    printf("%s\n", __func__);
}

void store_halfword(Word32_t instr) {
    printf("%s\n", __func__);
}

void store_word(Word32_t instr) {
    printf("%s\n", __func__);
}
