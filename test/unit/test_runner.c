#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(decode_instr) {
	RUN_TEST_CASE(decode_instr, decode_instr_r_type_alu_add);
	RUN_TEST_CASE(decode_instr, decode_instr_r_type_alu_sll);
	RUN_TEST_CASE(decode_instr, decode_instr_i_type_addi);
	RUN_TEST_CASE(decode_instr, decode_instr_j_type_j);
}

void run_all_tests() {
	RUN_TEST_GROUP(decode_instr);
}

int main(int argc, const char * argv[]) {
  return UnityMain(argc, argv, run_all_tests);
}