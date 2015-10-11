#include "test_helper.h"

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

Decoded_instr_t build_decoded_instr(const unsigned short type, const unsigned short op, const unsigned short rs, \
		const unsigned short rt, const unsigned short rd, const unsigned short shamt, const unsigned short funct, \
		const int imm, const int addr) {
	Decoded_instr_t dinstr;
	dinstr.opcode = op;
	if (R_TYPE == type) {
		dinstr.instr.r.rs = rs;
		dinstr.instr.r.rt = rt;
		dinstr.instr.r.rd = rd;
		dinstr.instr.r.shamt = shamt & SHAMT_MASK;
		dinstr.instr.r.funct = funct;
	} else if (I_TYPE == type) {
		dinstr.instr.i.rs = rs;
		dinstr.instr.i.rt = rt;
		dinstr.instr.i.imm = imm & IMM_MASK;
	} else if (J_TYPE == type) {
		dinstr.instr.j.addr = addr & ADDR_MASK;
	}
	return dinstr;
}

void test_instr(const Decoded_instr_t dinstr, const int type, const int op, const int rs, const int rt, \
		const int rd, const int shamt, const int funct, const int imm, const int addr) {
	TEST_ASSERT_EQUAL_MESSAGE(type, dinstr.instr_type, "instruction type mismatch\n");
	TEST_ASSERT_EQUAL_MESSAGE(op, dinstr.opcode, "bad opcode\n");
	if (R_TYPE == dinstr.instr_type) {
		TEST_ASSERT_EQUAL_MESSAGE(rs, dinstr.instr.r.rs, "bad rs\n");
		TEST_ASSERT_EQUAL_MESSAGE(rt, dinstr.instr.r.rt, "bad rt\n");
		TEST_ASSERT_EQUAL_MESSAGE(rd, dinstr.instr.r.rd, "bad rd\n");
		TEST_ASSERT_EQUAL_MESSAGE(shamt, dinstr.instr.r.shamt, "bad shamt\n");
		TEST_ASSERT_EQUAL_MESSAGE(funct, dinstr.instr.r.funct, "bad funct\n");
	} else if (I_TYPE == dinstr.instr_type) {
		TEST_ASSERT_EQUAL_MESSAGE(rs, dinstr.instr.i.rs, "bad rs\n");
		TEST_ASSERT_EQUAL_MESSAGE(rt, dinstr.instr.i.rt, "bad rt\n");
		TEST_ASSERT_EQUAL_MESSAGE(imm, dinstr.instr.i.imm, "bad immediate\n");
	} else if (J_TYPE == dinstr.instr_type) {
		TEST_ASSERT_EQUAL_MESSAGE(addr, dinstr.instr.j.addr, "bad address\n");
	} else {
		TEST_FAIL_MESSAGE("Invalid instruction type\n");
	}
}

void test_reg_result(Process_t *proc, const unsigned short reg_num, const Word32_t val) {
	char str[100];
	sprintf(str, "register %d, value incorrect", reg_num);
	TEST_ASSERT_TRUE(reg_num < proc->reg_file->num_regs);
	TEST_ASSERT_EQUAL_MESSAGE(val, proc->reg_file->regs[reg_num], str);
}

void init_regs(Process_t *proc, const unsigned short rs, const Word32_t rs_value, const unsigned short rt, \
        const Word32_t rt_value, const unsigned short rd, const Word32_t rd_value, const int pc) {
    proc->reg_file->regs[rs] = rs_value;
    proc->reg_file->regs[rt] = rt_value;
    proc->reg_file->regs[rd] = rd_value;
    proc->reg_file->pc = pc;
}
        
void test_alu_results(Process_t *proc, const unsigned short rs, const Word32_t rs_value, const unsigned short rt, \
        const Word32_t rt_value, const unsigned short rd, const Word32_t rd_value, const int pc) {
    test_reg_result(proc, rs, rs_value);
    test_reg_result(proc, rt, rt_value);
    test_reg_result(proc, rd, rd_value);
    TEST_ASSERT_EQUAL_MESSAGE(pc, proc->reg_file->pc, "program counter incorrect\n");
}