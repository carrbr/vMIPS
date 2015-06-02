#include "unity_fixture.h"
#include "instrs.h"

TEST_SETUP(alu_logical) {
	
}

TEST(alu_logical, alu_and_all_zeros) {
	Word32_t a = 0x00000000;
	Word32_t b = 0x00000000;	
}