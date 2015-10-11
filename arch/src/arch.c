#include "vmips.h" 
#include "arch.h" 
#include "instrs.h" 

const extern int32_t MAX_INT	= 0x7FFFFFFF;
const extern uint32_t U_MAX_INT	= 0xFFFFFFFF;
const extern int32_t MIN_INT 	= 0x80000000;
const extern uint32_t U_MIN_INT = 0x00000000;

Decoded_instr_t decode_instr(Word32_t instr) {
	Decoded_instr_t dinstr;
	DEBUG2_PRINT("INSTR %8X\n", instr);
	
	dinstr.opcode = instr >> OPCODE_SHIFT;
	
	// determine instruction type from opcode
	if (ALU_OP == dinstr.opcode || MFC0_OP == dinstr.opcode) { // R TYPE INSTR
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
	} else if (J_OP == dinstr.opcode || JAL_OP == dinstr.opcode) { // J TYPE INSTR
		dinstr.instr_type = J_TYPE;
		dinstr.instr.j.addr = instr & ADDR_MASK;
		DEBUG2_PRINT("\nOpcode: %X\nADDR: %X\n\n", dinstr.opcode, dinstr.instr.j.addr);
	} else { // I TYPE INSTR
		dinstr.instr_type = I_TYPE;
		dinstr.instr.i.imm = instr & IMM_MASK;
		instr >>= IMM_WIDTH;
			DEBUG2_PRINT("INSTR %8X\n", instr);
		dinstr.instr.i.rt = instr & SHAMT_AND_RX_MASK;
		instr >>= SHAMT_AND_RX_WIDTH;
			DEBUG2_PRINT("INSTR %8X\n", instr);
		dinstr.instr.i.rs = instr & SHAMT_AND_RX_MASK;
		DEBUG2_PRINT("\nOpcode: %X\nRS: %X\nRT: %X\nIMM: %X\n\n", dinstr.opcode, \
			dinstr.instr.i.rs, dinstr.instr.i.rt, dinstr.instr.i.imm);
	}
	return dinstr;
}

void print_decoded_instr(const Decoded_instr_t *di) {
	if (R_TYPE == di->instr_type) {
		DEBUG2_PRINT("Decoded Instr:\n\tOpcode: %X\n\tRS: %X\n\tRT: %X\n\tRD: %X\n\tSHAMT: %X\n\tFUNCT: %X\n", \
			di->opcode, di->instr.r.rs, di->instr.r.rt, di->instr.r.rd, di->instr.r.shamt, di->instr.r.funct);
	} else if (I_TYPE == di->instr_type) {
		DEBUG2_PRINT("Decoded Instr:\n\tOpcode: %X\n\tRS: %X\n\tRT: %X\n\tIMM: %X\n", \
			di->opcode, di->instr.i.rs, di->instr.i.rt, di->instr.i.imm);
	} else if (J_TYPE == di->instr_type) {
		DEBUG2_PRINT("Decoded Instr:\n\tOpcode: %X\n\tADDR: %X\n", di->opcode, di->instr.j.addr);
	} else {
		DEBUG2_PRINT("Invalid Instr type in decoded instr\n");
	}
}