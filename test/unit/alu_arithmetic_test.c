#include "test_helper.h"

TEST_GROUP(alu_arithmetic);

TEST_GROUP_RUNNER(alu_arithmetic) {
	// ADD Tests
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_add_zero_zero);
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_add_zero_one);
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_add_one_zero);
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_add_one_maxint);
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_add_zero_m_one);
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_add_m_one_zero);
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_add_m_one_minint);        
    
    // ADDU Tests
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_addu_zero_zero);
    
    // SUB Tests
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_sub_zero_zero);
    
    // SUBU Tests
    RUN_TEST_CASE(alu_arithmetic, alu_arithmetic_subu_zero_zero);
    
}
        
Process_t *proc;

TEST_SETUP(alu_arithmetic) {
	proc = build_process();
    TEST_ASSERT_TRUE_MESSAGE(proc != NULL, "failed to alloc proc");
    TEST_ASSERT_TRUE_MESSAGE(proc->reg_file != NULL, "failed to alloc proc reg file");
    TEST_ASSERT_TRUE_MESSAGE(proc->reg_file->regs != NULL, "failed to alloc proc reg file regs");
    TEST_ASSERT_TRUE_MESSAGE(proc->mem_space != NULL, "failed to alloc proc mem space");
}

TEST_TEAR_DOWN(alu_arithmetic) {
    cleanup(NULL, proc);
}

/**************************************************************************************************
 ********                                    ADD TESTS                                     ********
 **************************************************************************************************/

TEST(alu_arithmetic, alu_arithmetic_add_zero_zero) {
    const Word32_t rs_init  = 0;
    const Word32_t rt_init  = 0;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_arithmetic, alu_arithmetic_add_zero_one) {
    const Word32_t rs_init  = 0;
    const Word32_t rt_init  = 1;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 1;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_arithmetic, alu_arithmetic_add_one_zero) {
    const Word32_t rs_init  = 1;
    const Word32_t rt_init  = 0;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 1;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_arithmetic, alu_arithmetic_add_two_four) {
    const Word32_t rs_init  = 2;
    const Word32_t rt_init  = 4;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 6;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_arithmetic, alu_arithmetic_add_one_maxint) {
    const Word32_t rs_init  = 1;
    const Word32_t rt_init  = MAX_INT;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = MIN_INT;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}


TEST(alu_arithmetic, alu_arithmetic_add_zero_m_one) {
    const Word32_t rs_init  = 0;
    const Word32_t rt_init  = -1;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = -1;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_arithmetic, alu_arithmetic_add_m_one_zero) {
    const Word32_t rs_init  = -1;
    const Word32_t rt_init  = 0;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = -1;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_arithmetic, alu_arithmetic_add_m_one_m_two) {
    const Word32_t rs_init  = -1;
    const Word32_t rt_init  = -2;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = -3;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_arithmetic, alu_arithmetic_add_m_one_minint) {
    const Word32_t rs_init  = -1;
    const Word32_t rt_init  = MIN_INT;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = MAX_INT;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADD, BLANK, BLANK);
    alu_add_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}


/**************************************************************************************************
 ********                                    ADDU TESTS                                     ********
 **************************************************************************************************/

TEST(alu_arithmetic, alu_arithmetic_addu_zero_zero) {
    const Word32_t rs_init  = 0;
    const Word32_t rt_init  = 0;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, ADDU, BLANK, BLANK);
    alu_addu_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                    SUB TESTS                                     ********
 **************************************************************************************************/

TEST(alu_arithmetic, alu_arithmetic_sub_zero_zero) {
    const Word32_t rs_init  = 0;
    const Word32_t rt_init  = 0;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SUB, BLANK, BLANK);
    alu_sub_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                    SUBU TESTS                                     ********
 **************************************************************************************************/

TEST(alu_arithmetic, alu_arithmetic_subu_zero_zero) {
    const Word32_t rs_init  = 0;
    const Word32_t rt_init  = 0;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, SUBU, BLANK, BLANK);
    alu_subu_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}