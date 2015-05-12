#include "vmips.h"
#include "arch.h"
#include "instrs.h"
#include "debug.h"

Decoded_instr_t decode_instr(Word32_t instr) {
	Decoded_instr_t dinstr;
	
	dinstr.opcode = instr >> OPCODE_SHIFT;
	
	// determine instruction type from opcode
	if (ALU == dinstr.opcode || MFC0 == dinstr.opcode) { // R TYPE INSTR
		dinstr.instr_type = R_TYPE;
		dinstr.instr.r.funct = instr & FUNCT_MASK;
		instr >>= FUNCT_WIDTH;
		dinstr.instr.r.shamt = instr & SHAMT_AND_RX_MASK;
		instr >>= SHAMT_AND_RX_WIDTH;
		dinstr.instr.r.rd = instr & SHAMT_AND_RX_MASK;
		instr >>= SHAMT_AND_RX_WIDTH;
		dinstr.instr.r.rt = instr & SHAMT_AND_RX_MASK;
		instr >>= SHAMT_AND_RX_WIDTH;
		dinstr.instr.r.rs = instr & SHAMT_AND_RX_MASK;
		DEBUG2_PRINT("\nOpcode: %X\nRS: %X\nRT: %X\nRD: %X\nSHAMT: %X\nFUNCT: %X\n\n",\
			 dinstr.opcode, dinstr.instr.r.rs, dinstr.instr.r.rt, dinstr.instr.r.rd,\
			 dinstr.instr.r.shamt, dinstr.instr.r.funct);
	} else if (J == dinstr.opcode || JAL == dinstr.opcode) { // J TYPE INSTR
		dinstr.instr_type = J_TYPE;
		dinstr.instr.j.addr = instr & ADDR_MASK;
		DEBUG2_PRINT("\nOpcode: %X\nADDR: %X\n\n", dinstr.opcode, dinstr.instr.j.addr);
	} else { // I TYPE INSTR
		dinstr.instr_type = I_TYPE;
		dinstr.instr.i.imm = instr & IMM_MASK;
		instr >>= SHAMT_AND_RX_WIDTH;
		dinstr.instr.i.rt = instr & SHAMT_AND_RX_MASK;
		instr >>= SHAMT_AND_RX_WIDTH;
		dinstr.instr.i.rs = instr & SHAMT_AND_RX_MASK;
		DEBUG2_PRINT("\nOpcode: %X\nRS: %X\nRT: %X\nRD: %X\nIMM: %X\n\n", dinstr.opcode, \
			dinstr.instr.i.rs, dinstr.instr.i.rt, dinstr.instr.i.imm);
	}
	return dinstr;
}