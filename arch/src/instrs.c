#include "vmips.h" 
#include "arch.h" 
#include "instrs.h" 


/*
 * abstraction of ALU's function handling.
 *
 * This is a table of function pointers indexed by function code
 */
#define FUNC_CODE_COUNT 0x2C
static void (*funcs[FUNC_CODE_COUNT]) (Decoded_instr_t, Process_t *);


Opcode_table_t *init_opcode_table() {
    Opcode_table_t *opcodes = malloc(sizeof *opcodes);
    opcodes->num_opcodes = OPCODE_COUNT;
    opcodes->opcodes[ALU_OP] = alu_op;
    opcodes->opcodes[J_OP] = j_op;
    opcodes->opcodes[JAL_OP] = jal_op;
    opcodes->opcodes[BEQ_OP] = beq_op;
    opcodes->opcodes[BNE_OP] = bne_op;
    opcodes->opcodes[ADDI_OP] = addi_op;
    opcodes->opcodes[ADDIU_OP] = addiu_op;
    opcodes->opcodes[SLTI_OP] = slti_op;
    opcodes->opcodes[SLTIU_OP] = sltiu_op;
    opcodes->opcodes[ANDI_OP] = andi_op;
    opcodes->opcodes[ORI_OP] = ori_op;
    opcodes->opcodes[LUI_OP] = lui_op;
    opcodes->opcodes[MFC0_OP] = mfc0_op;
    opcodes->opcodes[LB_OP] = lb_op;
    opcodes->opcodes[LH_OP] = lh_op;
    opcodes->opcodes[LW_OP] = lw_op;
    opcodes->opcodes[LBU_OP] = lbu_op;
    opcodes->opcodes[LHU_OP] = lhu_op;
    opcodes->opcodes[SB_OP] = sb_op;
    opcodes->opcodes[SH_OP] = sh_op;
    opcodes->opcodes[SW_OP] = sw_op;
    
    /*
     * unimplemented operations
     *
     * we have empty slots in our table where MIPS has no opcode funcs
     * we are essentially trading space for lookup time and simplicity
     */
    opcodes->opcodes[0x01] = unimpl_op;
    opcodes->opcodes[0x06] = unimpl_op;
    opcodes->opcodes[0x07] = unimpl_op;
    opcodes->opcodes[0x0E] = unimpl_op;
    opcodes->opcodes[0x11] = unimpl_op;
    opcodes->opcodes[0x12] = unimpl_op;
    opcodes->opcodes[0x13] = unimpl_op;
    opcodes->opcodes[0x14] = unimpl_op;
    opcodes->opcodes[0x15] = unimpl_op;
    opcodes->opcodes[0x16] = unimpl_op;
    opcodes->opcodes[0x17] = unimpl_op;
    opcodes->opcodes[0x18] = unimpl_op;
    opcodes->opcodes[0x19] = unimpl_op;
    opcodes->opcodes[0x1A] = unimpl_op;
    opcodes->opcodes[0x1B] = unimpl_op;
    opcodes->opcodes[0x1C] = unimpl_op;
    opcodes->opcodes[0x1D] = unimpl_op;
    opcodes->opcodes[0x1E] = unimpl_op;
    opcodes->opcodes[0x1F] = unimpl_op;
    opcodes->opcodes[0x22] = unimpl_op;
    opcodes->opcodes[0x26] = unimpl_op;
    opcodes->opcodes[0x27] = unimpl_op;
    opcodes->opcodes[0x2A] = unimpl_op;
    
    init_alu_func_table();

    return opcodes;
}

void init_alu_func_table() {
    // implemented operations
    funcs[SLL] = alu_sll_op;
    funcs[SRL] = alu_srl_op;
    funcs[SRA] = alu_sra_op;
    funcs[SLLV] = alu_sllv_op;
    funcs[SRLV] = alu_srlv_op;
    funcs[JR] = alu_jr_op;
    funcs[SYSCALL] = alu_syscall_op;
    funcs[MFHI] = alu_mfhi_op;
    funcs[MFLO] = alu_mflo_op;
    funcs[MULT] = alu_mult_op;
    funcs[MULTU] = alu_multu_op;
    funcs[DIV] = alu_div_op;
    funcs[DIVU] = alu_divu_op;
    funcs[ADD] = alu_add_op;
    funcs[ADDU] = alu_addu_op;
    funcs[SUB] = alu_sub_op;
    funcs[SUBU] = alu_subu_op;
    funcs[AND] = alu_and_op;
    funcs[OR] = alu_or_op;
    funcs[XOR] = alu_xor_op;
    funcs[NOR] = alu_nor_op;
    funcs[SLT] = alu_slt_op;
    funcs[SLTU] = alu_sltu_op;
    
    /*
     * unimplemented operations
     *
     * we have empty slots in our table where MIPS has no ALU funcs
     * we are essentially trading space for lookup time and simplicity
     */
    funcs[0x01] = alu_unimpl_op;
    funcs[0x05] = alu_unimpl_op;
    funcs[0x07] = alu_unimpl_op;
    funcs[0x09] = alu_unimpl_op;
    funcs[0x0A] = alu_unimpl_op;
    funcs[0x0B] = alu_unimpl_op;
    funcs[0x0D] = alu_unimpl_op;
    funcs[0x0E] = alu_unimpl_op;
    funcs[0x0F] = alu_unimpl_op;
    funcs[0x11] = alu_unimpl_op;
    funcs[0x13] = alu_unimpl_op;
    funcs[0x14] = alu_unimpl_op;
    funcs[0x15] = alu_unimpl_op;
    funcs[0x16] = alu_unimpl_op;
    funcs[0x17] = alu_unimpl_op;
    funcs[0x1C] = alu_unimpl_op;
    funcs[0x1D] = alu_unimpl_op;
    funcs[0x1E] = alu_unimpl_op;
    funcs[0x1F] = alu_unimpl_op;
    funcs[0x28] = alu_unimpl_op;
    funcs[0x29] = alu_unimpl_op;
}

/*
 * Opcode handler implementations
 */
 
 // handler for all ALU functions
void alu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    
    funcs[instr.instr.r.funct](instr, proc);
}

// preserves upper nibble of current PC
#define JUMP_MASK 0xF0000000
// makes sure that jumps are 4-byte word aligned, as 2^2 = 4
#define JUMP_SHIFT 2

// Unconditional Jump
void j_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    if (0 <= instr.instr.j.addr && proc->mem_space->mem_words > instr.instr.j.addr) {
        proc->reg_file->pc &= JUMP_MASK;
        proc->reg_file->pc |= (instr.instr.j.addr << JUMP_SHIFT);
    } else {
        ERR_PRINT("Invalid Memory Address, out of bounds\n");
        proc->terminate = TRUE;
    }
}

// Jump And Link, stores PC + 4 to return to
void jal_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    if (0 <= instr.instr.j.addr && proc->mem_space->mem_words > instr.instr.j.addr) {
        proc->reg_file->regs[ra_REG] = proc->reg_file->pc + MEM_WORD_SIZE_BYTES; // save pc so we can return
        proc->reg_file->pc &= JUMP_MASK;
        proc->reg_file->pc |= (instr.instr.j.addr << JUMP_SHIFT);
    } else {
        ERR_PRINT("Invalid Memory Address, out of bounds\n");
        proc->terminate = TRUE;
    }
}

void beq_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    unimpl_op(instr, proc);
}

void bne_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    unimpl_op(instr, proc);
}

void addi_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    unimpl_op(instr, proc);
}

// Unsigned addition with immediate -- ignores overflow
void addiu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.i.rt] = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm;
    
    proc->reg_file->pc++;
}

void slti_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    unimpl_op(instr, proc);
}

void sltiu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    unimpl_op(instr, proc);
}

// And with immediate 
void andi_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.i.rt] = proc->reg_file->regs[instr.instr.i.rs] & proc->reg_file->regs[instr.instr.i.imm];
    
    proc->reg_file->pc++;
}

// Or with immediate
void ori_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.i.rt] = proc->reg_file->regs[instr.instr.i.rs] | proc->reg_file->regs[instr.instr.i.imm];
    
    proc->reg_file->pc++;
}

// Load upper immediate, stores immediate ad most significant halfword, and zeros out the least significant half word
void lui_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.i.rt] = (instr.instr.i.imm << HWORD_SHIFT);
    
    proc->reg_file->pc++;
}

// Don't have coprocessors in this vm, at least for now
void mfc0_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    unimpl_op(instr, proc);
}

// Load byte unsigned, least significant bits, sign extension performed
void lb_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    load_unit(addr, instr.instr.i.rt, proc, BYTE_MASK, BYTE_SIGN_MASK);
    
    proc->reg_file->pc++;
}

// Load halfword, least significant 16 bits, sign extension performed
void lh_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    load_unit(addr, instr.instr.i.rt, proc, HWORD_MASK, HWORD_SIGN_MASK);
    
    proc->reg_file->pc++;
}

// Load word
void lw_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    load_unit(addr, instr.instr.i.rt, proc, WORD_MASK, NO_SIGN_EX);
    
    proc->reg_file->pc++;
}

// Load byte unsigned, least significant 8 bits, no sign extension
void lbu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    load_unit(addr, instr.instr.i.rt, proc, BYTE_MASK, NO_SIGN_EX);
    
    proc->reg_file->pc++;
}

// Load halfword unsigned, least significant 16 bits, no sign extension
void lhu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    load_unit(addr, instr.instr.i.rt, proc, HWORD_MASK, NO_SIGN_EX);
    
    proc->reg_file->pc++;
}

// Store byte, least significant 8 bits
void sb_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    store_unit(instr.instr.i.rt, addr, proc, BYTE_MASK);
    
    proc->reg_file->pc++;
}

// Store halfword, least significant 16 bits
void sh_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    store_unit(instr.instr.i.rt, addr, proc, HWORD_MASK);
    
    proc->reg_file->pc++;
}

// Store word
void sw_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.i.rs] + instr.instr.i.imm; // add offset to base addr in reg
    store_unit(instr.instr.i.rt, addr, proc, WORD_MASK);
 
    proc->reg_file->pc++;
}

// unimplemented instruction handler -- terminates program
void unimpl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("UNIMPLEMENT OPERATION: CRASHING\n");
    proc->terminate = TRUE;
}

/*
 * helper func for loading and storing data
 */
void load_unit(const Word32_t src_addr, const Word32_t dest_reg, Process_t *const proc, const int unit_mask, const int sign_extend_mask) {
    if (0 <= src_addr && proc->mem_space->mem_words > src_addr) {
        /*
         * perform sign extension if necessary
         *
         * The NO_SIGN_EX macro should be passed as sign_extend_mask if no sign extension is to be performed.
         * This will ensure that this if condition fails, and thus we will initialize the word to 0x00000000
         * instead of 0xFFFFFFFF.
         */
        if (proc->mem_space->memory[src_addr] & unit_mask & sign_extend_mask) {
            proc->reg_file->regs[dest_reg] = SIGN_EX_MASK;      
        } else {
            proc->reg_file->regs[dest_reg] = unit_mask;
        }
        proc->reg_file->regs[dest_reg] &= proc->mem_space->memory[src_addr];
    } else {
        ERR_PRINT("Invalid Memory Address, out of bounds\n");
        proc->terminate = TRUE;
    }
}

void store_unit(const Word32_t src_reg, const Word32_t dest_addr, Process_t *const proc, const int unit_mask) {
    if (0 <= dest_addr && proc->mem_space->mem_words > dest_addr) {
        proc->mem_space->memory[dest_addr] = unit_mask;
        proc->mem_space->memory[dest_addr] &= proc->reg_file->regs[src_reg];
    } else {
        ERR_PRINT("Invalid Memory Address, out of bounds\n");
        proc->terminate = TRUE;
    }
}

/*
 * ALU function implementations
 */
 
 // Shift left logical
void alu_sll_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rt] << instr.instr.r.shamt;
    
    proc->reg_file->pc++;
}

/*
 * These masks are used to make sure we set the bits shifted in on a right shift properly
 * as it is implementation defined according to the C standard whether zeros or the sign
 * bit are shifted in on a right shift
 */
#define BIT_MASK_ONES     0xFFFFFFFF
#define MSB_MASK            0x80000000 // most significant bit

// Shift right logical -- zeros shifted in
void alu_srl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rt] >> instr.instr.r.shamt;
    
    // make sure shifted in bit is correct
    if (MSB_MASK & proc->reg_file->regs[instr.instr.r.rt]) {
        // MSB = 1, need to shift in zeros because logical shift
        proc->reg_file->regs[instr.instr.r.rd] &= BIT_MASK_ONES >> instr.instr.r.shamt;
    }
    
    proc->reg_file->pc++;
}

// Shift right arithmetic -- sign bit shifted in
void alu_sra_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rt] >> instr.instr.r.shamt;
    
    // make sure shifted in bit is correct
    if (MSB_MASK & proc->reg_file->regs[instr.instr.r.rt]) {
        // MSB = 1, need to shift in ones
        proc->reg_file->regs[instr.instr.r.rd] |= BIT_MASK_ONES << (proc->mem_space->word_size - instr.instr.r.shamt);
    }
    
    proc->reg_file->pc++;
}

void alu_sllv_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    if (proc->reg_file->regs[instr.instr.r.rs] < WORD_SIZE) {
        proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rt] << proc->reg_file->regs[instr.instr.r.rs];
    } else { // handle overflow case
        proc->reg_file->regs[instr.instr.r.rd] = 0;
    }
    
    proc->reg_file->pc++;
}

void alu_srlv_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    if (proc->reg_file->regs[instr.instr.r.rs] < WORD_SIZE) {
        proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rt] >> proc->reg_file->regs[instr.instr.r.rs];
    } else { // handle overflow case
        proc->reg_file->regs[instr.instr.r.rd] = 0;
    }
    
    proc->reg_file->pc++;
}

// Jump to address contained in register
void alu_jr_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    Word32_t addr = proc->reg_file->regs[instr.instr.r.rs];
    if (0 <= addr && proc->mem_space->mem_words > addr) {
        proc->reg_file->pc = addr;
    } else {
        ERR_PRINT("Invalid Memory Address, out of bounds\n");
        proc->terminate = TRUE;
    }
}

// SYSCALL ENUMS
#define SYSCALL_PRINT_INT       1
#define SYSCALL_PRINT_FLOAT     2
#define SYSCALL_PRINT_DOUBLE    3
#define SYSCALL_PRINT_STRING    4
#define SYSCALL_READ_INT        5
#define SYSCALL_READ_FLOAT      6
#define SYSCALL_READ_DOUBLE     7
#define SYSCALL_READ_STRING     8
#define SYSCALL_SBRK            9
#define SYSCALL_EXIT            10

// Syscall handler
void alu_syscall_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("SYSCALL FUNC\n");
    
    char *buffer_addr; // for use with the string calls
    switch(proc->reg_file->regs[v0_REG]) {
        case SYSCALL_PRINT_INT:
            DEBUG_PRINT("Print Int Syscall\n");
            VMIPS_PRINT("%d", proc->reg_file->regs[a0_REG]); // prints int in $a0
            break;
        case SYSCALL_PRINT_STRING:
            DEBUG_PRINT("Print String Syscall\n");
            buffer_addr = (char *)&(proc->mem_space->memory[proc->reg_file->regs[a0_REG]]);
            VMIPS_PRINT("%s", buffer_addr); // prints null-terminated string buffer at mem addr in $a0
            break;
        case SYSCALL_READ_INT:
            DEBUG_PRINT("Read Int Syscall\n");
            VMIPS_READ("%d", &(proc->reg_file->regs[v0_REG])); // reads int value into $v0
            break;
        case SYSCALL_READ_STRING:
            DEBUG_PRINT("Read String Syscall\n");
            int max_len = proc->reg_file->regs[a1_REG]; // $a1 contains maximum number of chars to read in
            // can't dynamically specify string specifier so we'll generate it.  A bit hacky but whatever for now...
            char format_string[20];
            buffer_addr = (char *)&(proc->mem_space->memory[proc->reg_file->regs[a0_REG]]);
            sprintf(format_string, "%%%ds", max_len);
            VMIPS_READ(format_string, buffer_addr); // store in buffer starting at addr in $a0
            break;
        case SYSCALL_EXIT:
            DEBUG_PRINT("Exit Syscall\n");
            proc->terminate = TRUE;
            break;
        default:
            ERR_PRINT("Unimplemented SYSCALL, 0x%X", proc->reg_file->regs[v0_REG]);
            proc->terminate = TRUE;
    }
    
    proc->reg_file->pc++;
}

void alu_mfhi_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

void alu_mflo_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

void alu_mult_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

void alu_multu_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

void alu_div_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

void alu_divu_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

void alu_add_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n"); // TODO check for overflow conditions

    // TODO: move this into a central addition routine
    // the if branches all currently do the same thing, return overflow or not
    int64_t t1 = safe_cast_int32_to_int64(proc->reg_file->regs[instr.instr.r.rs]);
    int64_t t2 = safe_cast_int32_to_int64(proc->reg_file->regs[instr.instr.r.rt]);
    int64_t double_size_result = t1 + t2;
    if (double_size_result > MAX_INT) { // overflow, number too large
        proc->reg_file->regs[instr.instr.r.rd] = (int32_t)double_size_result;
    } else if (double_size_result < MIN_INT) { // overflow, number too negative
        proc->reg_file->regs[instr.instr.r.rd] = (int32_t)double_size_result;
    } else { // no overflow
        proc->reg_file->regs[instr.instr.r.rd] = (int32_t)double_size_result;
    }
    
    proc->reg_file->pc++;
}

// Unisgned addition -- ignores overflow
void alu_addu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rs] + proc->reg_file->regs[instr.instr.r.rt];
    
    proc->reg_file->pc++;
}

// Signed subtraction
void alu_sub_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n"); // TODO check for overflow
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rs] - proc->reg_file->regs[instr.instr.r.rt];
    
    proc->reg_file->pc++;
}

// Unsigned subtractrion -- ignores overflow
void alu_subu_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rs] - proc->reg_file->regs[instr.instr.r.rt];
    
    proc->reg_file->pc++;
}

// Bitwise and
void alu_and_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rs] & proc->reg_file->regs[instr.instr.r.rt];
    proc->reg_file->pc++;
}

// Bitwise or
void alu_or_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rs] | proc->reg_file->regs[instr.instr.r.rt];
    
    proc->reg_file->pc++;
}

// Bitwise xor
void alu_xor_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rs] ^ proc->reg_file->regs[instr.instr.r.rt];
    
    proc->reg_file->pc++;
}

// Bitwise nor
void alu_nor_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("\n");
    proc->reg_file->regs[instr.instr.r.rd] = proc->reg_file->regs[instr.instr.r.rs] | proc->reg_file->regs[instr.instr.r.rt];
    proc->reg_file->regs[instr.instr.r.rd] = ~proc->reg_file->regs[instr.instr.r.rd];
    
    proc->reg_file->pc++;
}

void alu_slt_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

void alu_sltu_op(Decoded_instr_t instr, Process_t *proc) {
    alu_unimpl_op(instr, proc);
}

// unimplemented operation handler -- simply terminates program
void alu_unimpl_op(Decoded_instr_t instr, Process_t *proc) {
    DEBUG_PRINT("UNIMPLEMENTED OPERATION: CRASHING\n");
    proc->terminate = TRUE;
}

/*
 * Helper Functions
 */
#define SIGN_EXTENSION_MASK_32_to_64 0xFFFFFFFF00000000
int64_t safe_cast_int32_to_int64(const int32_t n) {
    if (n >= 0) {
        return (int64_t) n;
    } else { // need to perform sign extension
        return ((int64_t) n) | SIGN_EXTENSION_MASK_32_to_64;
    }
}