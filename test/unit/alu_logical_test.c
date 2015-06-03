#include "test_helper.h"

TEST_GROUP(alu_logical);

TEST_GROUP_RUNNER(alu_logical) {
	// AND Tests
    RUN_TEST_CASE(alu_logical, alu_logical_and_all_zeros);
    RUN_TEST_CASE(alu_logical, alu_logical_and_all_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_and_zeros_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_and_alternating_same);
    RUN_TEST_CASE(alu_logical, alu_logical_and_alternating_opposite);
    RUN_TEST_CASE(alu_logical, alu_logical_and_mask);
    RUN_TEST_CASE(alu_logical, alu_logical_and_rs_rt_same);
    RUN_TEST_CASE(alu_logical, alu_logical_and_rs_rd_same);
    RUN_TEST_CASE(alu_logical, alu_logical_and_all_same);
    
    // OR Tests
    RUN_TEST_CASE(alu_logical, alu_logical_or_all_zeros);
    RUN_TEST_CASE(alu_logical, alu_logical_or_all_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_or_zeros_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_or_alternating_same);
    RUN_TEST_CASE(alu_logical, alu_logical_or_alternating_opposite);
    RUN_TEST_CASE(alu_logical, alu_logical_or_mask);
    RUN_TEST_CASE(alu_logical, alu_logical_or_complex);
    RUN_TEST_CASE(alu_logical, alu_logical_or_rs_rt_same);
    RUN_TEST_CASE(alu_logical, alu_logical_or_rs_rd_same);
    RUN_TEST_CASE(alu_logical, alu_logical_or_all_same);
    
    // XOR Tests
    RUN_TEST_CASE(alu_logical, alu_logical_xor_all_zeros);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_all_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_zeros_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_alternating_same);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_alternating_opposite);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_mask);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_complex);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_rs_rt_same);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_rs_rd_same);
    RUN_TEST_CASE(alu_logical, alu_logical_xor_all_same);
    
    // NOR Tests
    RUN_TEST_CASE(alu_logical, alu_logical_nor_all_zeros);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_all_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_zeros_fs);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_alternating_same);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_alternating_opposite);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_mask);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_complex);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_rs_rt_same);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_rs_rd_same);
    RUN_TEST_CASE(alu_logical, alu_logical_nor_all_same);
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

/**************************************************************************************************
 ********                                    AND TESTS                                     ********
 **************************************************************************************************/

TEST(alu_logical, alu_logical_and_all_zeros) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_all_fs) {
    const Word32_t rs_init  = 0xFFFFFFFF;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x00000000;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_zeros_fs) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_alternating_same) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0xAAAAAAAA;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xAAAAAAAA;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_alternating_opposite) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0x55555555;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_mask) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x503BD2FC;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_rs_rd_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0x503BD2FC;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_rs_rt_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x503BD2FC;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, expected, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_and_all_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0x503BD2FC;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_and_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                     OR TESTS                                     ********
 **************************************************************************************************/

TEST(alu_logical, alu_logical_or_all_zeros) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_all_fs) {
    const Word32_t rs_init  = 0xFFFFFFFF;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x00000000;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_zeros_fs) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_alternating_same) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0xAAAAAAAA;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xAAAAAAAA;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_alternating_opposite) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0x55555555;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_mask) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_complex) {
    const Word32_t rs_init  = 0x503BD2FC; // 0b 0101 0000 0011 1011 1101 0010 1111 1100
    const Word32_t rt_init  = 0x24D1EEF7; // 0b 0010 0100 1101 0001 1110 1110 1111 0111
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x74FBFEFF; // 0b 0111 0100 1111 1011 1111 1110 1111 1111
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_rs_rd_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_rs_rt_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x503BD2FC;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_or_all_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0x503BD2FC;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_or_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, expected, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                    XOR TESTS                                     ********
 **************************************************************************************************/

TEST(alu_logical, alu_logical_xor_all_zeros) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_all_fs) {
    const Word32_t rs_init  = 0xFFFFFFFF;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x00000000;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_zeros_fs) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_alternating_same) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0xAAAAAAAA;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_alternating_opposite) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0x55555555;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_mask) {
    const Word32_t rs_init  = 0x503BD2FC; // 0x 0101 0000 0011 1011 1101 0010 1111 1100
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xAFC42D03; // 0x 1010 1111 1100 0100 0010 1101 0000 0011
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_complex) {
    const Word32_t rs_init  = 0x503BD2FC; // 0b 0101 0000 0011 1011 1101 0010 1111 1100
    const Word32_t rt_init  = 0x24D1EEF7; // 0b 0010 0100 1101 0001 1110 1110 1111 0111
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x74EA3C0B; // 0b 0111 0100 1110 1010 0011 1100 0000 1011
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_rs_rd_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0xAFC42D03;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_rs_rt_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_xor_all_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_xor_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, expected, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                    NOR TESTS                                     ********
 **************************************************************************************************/

TEST(alu_logical, alu_logical_nor_all_zeros) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0x00000000;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xFFFFFFFF;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_all_fs) {
    const Word32_t rs_init  = 0xFFFFFFFF;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x00000000;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, AND, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_zeros_fs) {
    const Word32_t rs_init  = 0x00000000;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_alternating_same) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0xAAAAAAAA;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x55555555;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_alternating_opposite) {
    const Word32_t rs_init  = 0xAAAAAAAA;
    const Word32_t rt_init  = 0x55555555;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_mask) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_complex) {
    const Word32_t rs_init  = 0x503BD2FC; // 0b 0101 0000 0011 1011 1101 0010 1111 1100
    const Word32_t rt_init  = 0x24D1EEF7; // 0b 0010 0100 1101 0001 1110 1110 1111 0111
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0x8B040100; // 0b 1000 1011 0000 0100 0000 0001 0000 0000
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_rs_rd_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0xFFFFFFFF;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0x00000000;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a2_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_rs_rt_same) {
    const Word32_t rs_init  = 0x503BD2FC; // 0b 0101 0000 0011 1011 1101 0010 1111 1100
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0xFFFFFFFF;
    const Word32_t expected = 0xAFC42D03; // 0b 1010 1111 1100 0100 0010 1101 0000 0011
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = v0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, rs_init, rt, rt_init, rd, expected, pc + 1);
}

TEST(alu_logical, alu_logical_nor_all_same) {
    const Word32_t rs_init  = 0x503BD2FC;
    const Word32_t rt_init  = 0x503BD2FC;
    const Word32_t rd_init  = 0x503BD2FC;
    const Word32_t expected = 0xAFC42D03;
    const unsigned short rs = a0_REG;
    const unsigned short rt = a0_REG;
    const unsigned short rd = a0_REG;
    const unsigned short pc = 256;
    
    init_regs(proc, rs, rs_init, rt, rt_init, rd, rd_init, pc);
	Decoded_instr_t dinstr = build_decoded_instr(R_TYPE, ALU_OP, rs, rt, rd, BLANK, OR, BLANK, BLANK);
    alu_nor_op(dinstr, proc);
    test_alu_results(proc, rs, expected, rt, expected, rd, expected, pc + 1);
}

/**************************************************************************************************
 ********                                 Helper Functions                                 ********
 **************************************************************************************************/

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