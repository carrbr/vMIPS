#include <stdio.h>
#include <stdlib.h>
#include "vmips.h"
#include "hardware.h"
#include "instrs.h"
#include "errors.h"
#include "debug.h"

void cleanup(Arch_info_t *arch, Process_t *proc);
int load_mips_object_file(char *fname, Process_t *proc, uint32_t addr_offset);
void init_processor(Process_t *proc);

int terminate = FALSE;

int main(int argc, char *argv[]) {
    int i;
    
    Word32_t instr;
    Decoded_instr_t dinstr;
    
    // make sure we were passed a MIPS binary file
    if (argc < 2) {
        ERR_PRINT("We are having a bad problem and you will not go to space today.\n");
        exit(1);
    }

    // begin init routines
    Process_t *proc = build_process();
        Arch_info_t *arch = arch_init();
    if (load_mips_object_file(argv[BIN_FILE_NAME], proc, START_ADDR)) {
        DEBUG_PRINT("ERR %s: failed to load object file", __FUNCTION__);
        cleanup(arch, proc);
        exit(1);
    }
    
    // main exec loop
    while (!terminate) {
        instr = proc->mem_space->memory[START_ADDR + i];
        if (instr != 0) { // ensure not NOOP
            dinstr = decode_instr(instr);
            arch->opcode_table->opcodes[dinstr.opcode](dinstr, proc);
        }
        i++;
    }
    
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
    proc->reg_file->regs[0] = 0; // this reg is always $zero in real MIPS
    proc->mem_space = init_memory_space();
    
    init_processor(proc);
    
    return proc;
}

void init_processor(Process_t *proc) {
    proc->reg_file->status = 0;
    proc->reg_file->pc = START_ADDR;
    proc->reg_file->regs[sp_REG] = proc->mem_space->word_size - 1; // start stack at top of mem space
    proc->reg_file->regs[fp_REG] = proc->reg_file->regs[sp_REG]; 
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