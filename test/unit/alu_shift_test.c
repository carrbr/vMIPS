#include "test_helper.h"

TEST_GROUP(alu_shift);

TEST_GROUP_RUNNER(alu_shift) {
	// SLL Tests
    RUN_TEST_CASE(alu_shift, alu_shift_sll_all_zeros_8);
    RUN_TEST_CASE(alu_shift, alu_shift_sll_all_ones_8);
    RUN_TEST_CASE(alu_shift, alu_shift_sll_all_zeros_31);
    RUN_TEST_CASE(alu_shift, alu_shift_sll_all_ones_31);
    RUN_TEST_CASE(alu_shift, alu_shift_sll_mixed_16);
    
    // SRL Tests
    RUN_TEST_CASE(alu_shift, alu_shift_srl_all_zeros_8);
    RUN_TEST_CASE(alu_shift, alu_shift_srl_all_ones_8);
    RUN_TEST_CASE(alu_shift, alu_shift_srl_all_zeros_31);
    RUN_TEST_CASE(alu_shift, alu_shift_srl_all_ones_31);
    RUN_TEST_CASE(alu_shift, alu_shift_srl_mixed_msb_one_16);
    RUN_TEST_CASE(alu_shift, alu_shift_srl_mixed_msb_zero_16);
    
    // SRA Tests
    RUN_TEST_CASE(alu_shift, alu_shift_sra_all_zeros_8);
    RUN_TEST_CASE(alu_shift, alu_shift_sra_all_ones_8);
    RUN_TEST_CASE(alu_shift, alu_shift_sra_all_zeros_31);
    RUN_TEST_CASE(alu_shift, alu_shift_sra_all_ones_31);
    RUN_TEST_CASE(alu_shift, alu_shift_sra_mixed_msb_one_16);
    RUN_TEST_CASE(alu_shift, alu_shift_sra_mixed_msb_zero_16);
    
    // SLLV Tests
    RUN_TEST_CASE(alu_shift, alu_shift_sllv_all_zeros_8);
    RUN_TEST_CASE(alu_shift, alu_shift_sllv_all_ones_8);
    RUN_TEST_CASE(alu_shift, alu_shift_sllv_all_zeros_31);
    RUN_TEST_CASE(alu_shift, alu_shift_sllv_all_ones_31);
    RUN_TEST_CASE(alu_shift, alu_shift_sllv_mixed_16);
    RUN_TEST_CASE(alu_shift, alu_shift_sllv_out);
    
    // SRLV Tests
    RUN_TEST_CASE(alu_shift, alu_shift_srlv_all_zeros_8);
    RUN_TEST_CASE(alu_shift, alu_shift_srlv_all_ones_8);
    RUN_TEST_CASE(alu_shift, alu_shift_srlv_all_zeros_31);
    RUN_TEST_CASE(alu_shift, alu_shift_srlv_all_ones_31);
    RUN_TEST_CASE(alu_shift, alu_shift_srlv_mixed_16);
    RUN_TEST_CASE(alu_shift, alu_shift_srlv_out_msb_one);
    RUN_TEST_CASE(alu_shift, alu_shift_srlv_out_msb_zero);
}

void init_regs(Process_t *proc, const unsigned short rs, const Word32_t rs_value, const unsigned short rt, \
        const Word32_t rt_value, const unsigned short rd, const Word32_t rd_value, const int pc);
void test_alu_results(Process_t *proc, const unsigned short rs, const Word32_t rs_value, const unsigned short rt, \
        const Word32_t rt_value, const unsigned short rd, const Word32_t rd_value, const int pc);
        
Process_t *proc;

TEST_SETUP(alu_shift) {
	proc = build_process();
    TEST_ASSERT_TRUE_MESSAGE(proc != NULL, "failed to alloc proc");
    TEST_ASSERT_TRUE_MESSAGE(proc->reg_file != NULL, "failed to alloc proc reg file");
    TEST_ASSERT_TRUE_MESSAGE(proc->reg_file->regs != NULL, "failed to alloc proc reg file regs");
    TEST_ASSERT_TRUE_MESSAGE(proc->mem_space != NULL, "failed to alloc proc mem space");
}

TEST_TEAR_DOWN(alu_shift) {
    cleanup(NULL, proc);
}

/**************************************************************************************************
 ********                                    SLL TESTS                                     ********
 **************************************************************************************************/

TEST(alu_shift, alu_shift_sll_all_zeros_8) {
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short shamt = 8;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SLL, BLANK, BLANK);
    alu_sll_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sll_all_ones_8) {
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFF00;
    const unsigned short shamt = 8;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SLL, BLANK, BLANK);
    alu_sll_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sll_all_zeros_31) {
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short shamt = 31;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SLL, BLANK, BLANK);
    alu_sll_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sll_all_ones_31) {
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x80000000;
    const unsigned short shamt = 31;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SLL, BLANK, BLANK);
    alu_sll_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sll_mixed_16) {
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xCD1B0000;
    const unsigned short shamt = 16;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SLL, BLANK, BLANK);
    alu_sll_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                    SRL TESTS                                     ********
 **************************************************************************************************/

TEST(alu_shift, alu_shift_srl_all_zeros_8) {
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short shamt = 8;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRL, BLANK, BLANK);
    alu_srl_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srl_all_ones_8) {
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00FFFFFF;
    const unsigned short shamt = 8;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRL, BLANK, BLANK);
    alu_srl_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srl_all_zeros_31) {
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short shamt = 31;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRL, BLANK, BLANK);
    alu_srl_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srl_all_ones_31) {
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000001;
    const unsigned short shamt = 31;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRL, BLANK, BLANK);
    alu_srl_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srl_mixed_msb_one_16) {
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x0000A236;
    const unsigned short shamt = 16;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRL, BLANK, BLANK);
    alu_srl_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srl_mixed_msb_zero_16) {
    const Word32_t rt_init  = 0x2236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00002236;
    const unsigned short shamt = 16;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRL, BLANK, BLANK);
    alu_srl_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                    SRA TESTS                                     ********
 **************************************************************************************************/

TEST(alu_shift, alu_shift_sra_all_zeros_8) {
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short shamt = 8;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRA, BLANK, BLANK);
    alu_sra_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sra_all_ones_8) {
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short shamt = 8;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRA, BLANK, BLANK);
    alu_sra_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sra_all_zeros_31) {
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short shamt = 31;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRA, BLANK, BLANK);
    alu_sra_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sra_all_ones_31) {
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short shamt = 31;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRA, BLANK, BLANK);
    alu_sra_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sra_mixed_msb_one_16) {
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFA236;
    const unsigned short shamt = 16;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRA, BLANK, BLANK);
    alu_sra_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sra_mixed_msb_zero_16) {
    const Word32_t rt_init  = 0x2236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00002236;
    const unsigned short shamt = 16;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, BLANK, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, shamt, SRA, BLANK, BLANK);
    alu_sra_op(dinstr, proc);
    test_alu_results(proc, rs, BLANK, rt, rt_init, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                   SLLV TESTS                                     ********
 **************************************************************************************************/

TEST(alu_shift, alu_shift_sllv_all_zeros_8) {
    const Word32_t rs_init  = 0x00000008;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SLLV, BLANK, BLANK);
    alu_sllv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sllv_all_ones_8) {
    const Word32_t rs_init  = 0x00000008;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFF00;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SLLV, BLANK, BLANK);
    alu_sllv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sllv_all_zeros_31) {
    const Word32_t rs_init  = 0x0000001F;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SLLV, BLANK, BLANK);
    alu_sllv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sllv_all_ones_31) {
    const Word32_t rs_init  = 0x0000001F;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x80000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SLLV, BLANK, BLANK);
    alu_sllv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sllv_mixed_16) {
    const Word32_t rs_init  = 0x00000010;
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xCD1B0000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SLLV, BLANK, BLANK);
    alu_sllv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_sllv_out) {
    const Word32_t rs_init  = 0x00000021;
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SLLV, BLANK, BLANK);
    alu_sllv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                   SRLV TESTS                                     ********
 **************************************************************************************************/

TEST(alu_shift, alu_shift_srlv_all_zeros_8) {
    const Word32_t rs_init  = 0x00000008;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SRLV, BLANK, BLANK);
    alu_srlv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srlv_all_ones_8) {
    const Word32_t rs_init  = 0x00000008;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00FFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SRLV, BLANK, BLANK);
    alu_srlv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srlv_all_zeros_31) {
    const Word32_t rs_init  = 0x0000001F;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SRLV, BLANK, BLANK);
    alu_srlv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srlv_all_ones_31) {
    const Word32_t rs_init  = 0x0000001F;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000001;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SRLV, BLANK, BLANK);
    alu_srlv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srlv_mixed_16) {
    const Word32_t rs_init  = 0x00000010;
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x0000A236;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SRLV, BLANK, BLANK);
    alu_srlv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srlv_out_msb_one) {
    const Word32_t rs_init  = 0x00000021;
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SRLV, BLANK, BLANK);
    alu_srlv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_shift, alu_shift_srlv_out_msb_zero) {
    const Word32_t rs_init  = 0x00000021;
    const Word32_t rt_init  = 0xA236CD1B;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 14;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SRLV, BLANK, BLANK);
    alu_srlv_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}