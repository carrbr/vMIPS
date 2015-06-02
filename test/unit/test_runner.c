#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(decode_instr) {
	RUN_TEST_CASE(decode_instr, decode_instr_alu_add_op);
}

void run_all_tests() {
	RUN_TEST_GROUP(decode_instr);
}

int main(int argc, const char * argv[]) {
  return UnityMain(argc, argv, run_all_tests);
}