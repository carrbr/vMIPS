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


Word32_t build_instr(const int type, const int op, const int rs, const int rt, const int rd, \
		const int shamt, const int func, const int imm, const int addr);

TEST_GROUP(decode_instr);

TEST_SETUP(decode_instr) {
}

TEST_TEAR_DOWN(decode_instr) {
}

TEST(decode_instr, decode_instr_alu_add_op) {
	Word32_t instr = build_instr(R_TYPE, ALU_OP, a0_REG, a1_REG, a2_REG, BLANK, ADD, BLANK, BLANK);
	Decoded_instr_t dinstr = decode_instr(instr);
	
	TEST_ASSERT_EQUAL(R_TYPE, dinstr.instr_type);
	TEST_ASSERT_EQUAL(ALU_OP, dinstr.opcode);
	TEST_ASSERT_EQUAL(a0_REG, dinstr.instr.r.rs);
	TEST_ASSERT_EQUAL(a1_REG, dinstr.instr.r.rt);
	TEST_ASSERT_EQUAL(a2_REG, dinstr.instr.r.rd);
	TEST_ASSERT_EQUAL(ADD, dinstr.instr.r.funct);
}

Word32_t build_instr(const int type, const int op, const int rs, const int rt, const int rd, \
		const int shamt, const int func, const int imm, const int addr) {
	Word32_t instr = (op << OPCODE_SHAMT);
	if (R_TYPE == type) {
		instr |= (rs << RS_SHAMT);
		instr |= (rt << RT_SHAMT);
		instr |= (rd << RD_SHAMT);
		instr |= (shamt << SHAMT_SHAMT);
		instr |= func;
	}
	return instr;
}