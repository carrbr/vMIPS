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

#define SHAMT_MASK	0x0000001F
#define IMM_MASK	0x0000FFFF
#define ADDR_MASK	0x03FFFFFF

Word32_t build_instr(const int type, const int op, const int rs, const int rt, const int rd, \
		const int shamt, const int func, const int imm, const int addr);
Decoded_instr_t build_decoded_instr(const unsigned short type, const unsigned short op, const unsigned short rs, \
		const unsigned short rt, const unsigned short rd, const unsigned short shamt, const unsigned short funct, \
		const int imm, const int addr);
void test_instr(const Decoded_instr_t dinstr, const int type, const int op, const int rs, const int rt, \
		const int rd, const int shamt, const int funct, const int imm, const int addr);
void test_reg_result(Process_t *proc, const unsigned short reg_num, const Word32_t val);