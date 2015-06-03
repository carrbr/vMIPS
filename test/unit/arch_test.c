#include "unity.h"
#include "unity_fixture.h"
#include "arch.h"
#include "instrs.h"

#define BLANK 0x00000000
#define OPCODE_SHAMT	26
#define RS_SHAMT		21
#define RT_SHAMT		16
#define RD_SHAMT		11
#define SHAMT_SHAMT		6

#define SHAMT_MASK	0x0000001F
#define IMM_MASK	0x0000FFFF
#define ADDR_MASK	0x03FFFFFF


Word32_t build_instr(const int type, const int op, const int rs, const int rt, const int rd, \
		const int shamt, const int func, const int imm, const int addr);
void test_instr(const Decoded_instr_t dinstr, const int type, const int op, const int rs, const int rt, \
		const int rd, const int shamt, const int funct, const int imm, const int addr);

TEST_GROUP(decode_instr);

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

Word32_t build_instr(const int type, const int op, const int rs, const int rt, const int rd, \
		const int shamt, const int funct, const int imm, const int addr) {
	Word32_t instr = (op << OPCODE_SHAMT);
	if (R_TYPE == type) {
		instr |= (rs << RS_SHAMT);
		instr |= (rt << RT_SHAMT);
		instr |= (rd << RD_SHAMT);
		instr |= (shamt << (SHAMT_SHAMT & SHAMT_MASK));
		instr |= funct;
	} else if (I_TYPE == type) {
		instr |= (rs << RS_SHAMT);
		instr |= (rt << RT_SHAMT);
		instr |= imm & IMM_MASK;
	} else if (J_TYPE == type) {
		instr |= addr & ADDR_MASK;
	}
	return instr;
}

void test_instr(const Decoded_instr_t dinstr, const int type, const int op, const int rs, const int rt, \
		const int rd, const int shamt, const int funct, const int imm, const int addr) {
	TEST_ASSERT_EQUAL_MESSAGE(type, dinstr.instr_type, "instruction type mismatch");
	TEST_ASSERT_EQUAL_MESSAGE(op, dinstr.opcode, "bad opcode");
	if (R_TYPE == dinstr.instr_type) {
		TEST_ASSERT_EQUAL_MESSAGE(rs, dinstr.instr.r.rs, "bad rs");
		TEST_ASSERT_EQUAL_MESSAGE(rt, dinstr.instr.r.rt, "bad rt");
		TEST_ASSERT_EQUAL_MESSAGE(rd, dinstr.instr.r.rd, "bad rd");
		TEST_ASSERT_EQUAL_MESSAGE(shamt, dinstr.instr.r.shamt, "bad shamt");
		TEST_ASSERT_EQUAL_MESSAGE(funct, dinstr.instr.r.funct, "bad funct");
	} else if (I_TYPE == dinstr.instr_type) {
		TEST_ASSERT_EQUAL_MESSAGE(rs, dinstr.instr.i.rs, "bad rs");
		TEST_ASSERT_EQUAL_MESSAGE(rt, dinstr.instr.i.rt, "bad rt");
		TEST_ASSERT_EQUAL_MESSAGE(imm, dinstr.instr.i.imm, "bad immediate");
	} else if (J_TYPE == dinstr.instr_type) {
		TEST_ASSERT_EQUAL_MESSAGE(addr, dinstr.instr.j.addr, "bad address");
	} else {
		TEST_FAIL_MESSAGE("Invalid instruction type");
	}
}