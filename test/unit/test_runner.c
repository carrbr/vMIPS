#include "unity.h"
#include "unity_fixture.h"

void run_all_tests() {
	RUN_TEST_GROUP(decode_instr);
	RUN_TEST_GROUP(alu_logical);
	RUN_TEST_GROUP(alu_shift);
}

int main(int argc, const char * argv[]) {
  return UnityMain(argc, argv, run_all_tests);
}