#include <stdio.h>
#include <stdlib.h>
#include "vmips.h"
#include "hardware.h"
#include "instrs.h"
#include "errors.h"
#include "debug.h"

void cleanup(Arch_info_t *arch, Process_t *proc);
int load_mips_object_file(char *fname, Process_t *proc, uint32_t addr_offset);

int main() {

    Process_t *proc = build_process();

    // just perform some tests to make sure everything is working properly

    // iterate through reg file
    int i;
    for (i = 0; i < proc->reg_file->num_regs; i++) {
        proc->reg_file->regs[i] = i + 1;
    }

    for (i = 0; i < proc->reg_file->num_regs; i++) {
        printf("Reg[%d]: %d\n", i, proc->reg_file->regs[i]);
    }

    // iterate through memory space
    for (i = 0; i < proc->mem_space->mem_words; i++) {
        proc->mem_space->memory[i] = i + 1;
    }

    for (i = 0; i < proc->mem_space->mem_words; i++) {
        printf("Memory[%d]: %d\n", i, proc->mem_space->memory[i]);
    }
    
    if (load_mips_object_file("C:\\Users\\carrb_000\\Documents\\MIPS\\mips1.o", proc, START_ADDR)) {
        DEBUG_PRINT("ERR %s: failed to load object file", __FUNCTION__);
        cleanup(NULL, proc);
        exit(1);
    }
    Word32_t instr;
    Decoded_instr_t dinstr;
    
    for (i = 0; i < 10; i++) {
        instr = proc->mem_space->memory[START_ADDR + i]; // 0b11110011 01101110 10010011 10010000
        dinstr = decode_instr(instr); // TODO make sure we check for NOOPs
    }
            
    //Word32_t instr = 0x036E9390; // 0b00000011 01101110 10010011 10010000
    instr = 0x00A62020; // 0b11110011 01101110 10010011 10010000
    dinstr = decode_instr(instr); // TODO make sure we check for NOOPs
    
    // try to use opcode table
    Arch_info_t *arch = arch_init();
    arch->opcode_table->opcodes[dinstr.opcode](dinstr, proc);
    
    instr = 0x0B6E9390; // 0b00001011 01101110 10010011 10010000
    dinstr = decode_instr(instr);
    
    instr = 0x436E9390; // 0b01000011 01101110 10010011 10010000
    dinstr = decode_instr(instr);

    cleanup(arch, proc);
    return 0;
}

void cleanup(Arch_info_t *arch, Process_t *proc) {
    free(arch->opcode_table);
    free(arch);
    free(proc->mem_space);
    free(proc->reg_file);
    free(proc);
}

Process_t *build_process() {    
    // setup environment for code execution
    Process_t *proc = malloc(sizeof(Process_t));
    proc->reg_file = init_reg_file();
    proc->mem_space = init_memory_space();
    return proc;
}

int load_mips_object_file(char *fname, Process_t *proc, uint32_t addr_offset) {
    FILE *file = fopen(fname, "rb");
    long fsize = -1;
    size_t result;
    
    // sanity check params
    if (fname == NULL || proc == NULL) {
        DEBUG_PRINT("ERR %s: null args\n", __FUNCTION__);
        return ERR_INVALID_ARGS;
    }
    if (addr_offset >= MEM_SIZE_IN_WORDS) {
        DEBUG_PRINT("ERR %s: addr_offset %d too large\n", __FUNCTION__, addr_offset);
        return ERR_INVALID_ARGS;
    }
    
    if (file == NULL) {
        DEBUG_PRINT("ERR %s: Failed to open %s\n", __FUNCTION__, fname);
        return ERR_CANT_OPEN_FILE;
    }
    
    // get file size and check if we have enough space
    fseek(file, 0, SEEK_END);
    fsize = ftell(file);
    if (fsize >= (proc->mem_space->mem_words * proc->mem_space->word_size_bytes - addr_offset)) {
        DEBUG_PRINT("ERR %s: File too large, not enough space in memory\n", __FUNCTION__);
        fclose(file);
        return ERR_FILE_TOO_LARGE;
    } else if (fsize > (proc->mem_space->mem_words * proc->mem_space->word_size_bytes) / 4) {
        DEBUG_PRINT("ERR %s: Warning: file occupies more than 1/4 of memory\n", __FUNCTION__);
    }
    rewind(file);
    
    // copy file contents into proc mem space
    result = fread(proc->mem_space->memory + addr_offset, 1, fsize, file);
    if (result != fsize) {
        DEBUG_PRINT("ERR %s: Couldn't read file %s\n", __FUNCTION__, fname);
        fclose(file);
        return ERR_FILE_READ;
    }
    
    fclose(file);
    return 0;
}