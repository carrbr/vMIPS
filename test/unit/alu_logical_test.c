#include "test_helper.h"

TEST_GROUP(alu_logical);

TEST_GROUP_RUNNER(alu_logical) {
	RUN_TEST_CASE(alu_logical, alu_logical_and_all_zeros);
}

void init_regs(Process_t *proc, const unsigned short rs, const Word32_t rs_value, const unsigned short rt, \
        const Word32_t rt_value, const unsigned short rd, const Word32_t rd_value, const int pc);
void test_alu_results(Process_t *proc, const unsigned short rs, const Word32_t rs_value, const unsigned short rt, \
        const Word32_t rt_value, const unsigned short rd, const Word32_t rd_value, const int pc);
        
Process_t *proc;

TEST_SETUP(alu_logical) {
	proc = build_process();
    TEST_ASSERT_TRUE_MESSAGE(proc != NULL, "failed to alloc proc");
    TEST_ASSERT_TRUE_MESSAGE(proc->reg_file != NULL, "failed to alloc proc reg file");
    TEST_ASSERT_TRUE_MESSAGE(proc->reg_file->regs != NULL, "failed to alloc proc reg file regs");
    TEST_ASSERT_TRUE_MESSAGE(proc->mem_space != NULL, "failed to alloc proc mem space");
}

TEST_TEAR_DOWN(alu_logical) {
    cleanup(NULL, proc);
}

TEST(alu_logical, alu_logical_and_all_zeros) {
    const Word32_t rs_init = 0x00000000;
    const Word32_t rt_init = 0x00000000;
    const Word32_t rd_init = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, 0x00000000, pc + 1);
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
    TEST_ASSERT_EQUAL_MESSAGE(pc, proc->reg_file->pc, "program counter incorrect");
}