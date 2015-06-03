#include "test_helper.h"

#define BLANK 0x00000000
#define OPCODE_SHAMT	26
#define RS_SHAMT		21
#define RT_SHAMT		16
#define RD_SHAMT		11
#define SHAMT_SHAMT		6

#define SHAMT_MASK	0x0000001F
#define IMM_MASK	0x0000FFFF
#define ADDR_MASK	0x03FFFFFF

TEST_GROUP(decode_instr);

TEST_GROUP_RUNNER(decode_instr) {
	RUN_TEST_CASE(decode_instr, decode_instr_r_type_alu_add);
	RUN_TEST_CASE(decode_instr, decode_instr_r_type_alu_sll);
	RUN_TEST_CASE(decode_instr, decode_instr_i_type_addi);
	RUN_TEST_CASE(decode_instr, decode_instr_j_type_j);
}

TEST_SETUP(decode_instr) {
}

TEST_TEAR_DOWN(decode_instr) {
}

TEST(decode_instr, decode_instr_r_type_alu_add) {
	Word32_t instr = build_instr(R_TYPE, ALU_OP, a0_REG, a1_REG, a2_REG, BLANK, ADD, BLANK, BLANK);
	Decoded_instr_t dinstr = decode_instr(instr);
	
	test_instr(dinstr, R_TYPE, ALU_OP, a0_REG, a1_REG, a2_REG, BLANK, ADD, BLANK, BLANK);
}

TEST(decode_instr, decode_instr_r_type_alu_sll) {
	Word32_t instr = build_instr(R_TYPE, ALU_OP, a0_REG, a1_REG, a2_REG, 0x00000013, SLL, BLANK, BLANK);
	Decoded_instr_t dinstr = decode_instr(instr);
	
	test_instr(dinstr, R_TYPE, ALU_OP, a0_REG, a1_REG, a2_REG, 0x00000013, SLL, BLANK, BLANK);
}

TEST(decode_instr, decode_instr_i_type_addi) {
	Word32_t instr = build_instr(I_TYPE, ADDI_OP, a0_REG, v0_REG, BLANK, BLANK, BLANK, 0x00001234, BLANK);
	Decoded_instr_t dinstr = decode_instr(instr);
	
	test_instr(dinstr, I_TYPE, ADDI_OP, a0_REG, v0_REG, BLANK, BLANK, BLANK, 0x00001234, BLANK);
}

TEST(decode_instr, decode_instr_j_type_j) {
	Word32_t instr = build_instr(J_TYPE, J_OP, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, 0x03456789);
	Decoded_instr_t dinstr = decode_instr(instr);
	
	test_instr(dinstr, J_TYPE, J_OP, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, 0x03456789);
}