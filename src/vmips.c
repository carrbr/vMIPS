#include "vmips.h" 
#include "hardware.h" 
#include "instrs.h" 

int load_mips_object_file(char *fname, Process_t *proc, uint32_t addr_offset);

int main(int argc, char *argv[]) {
    Word32_t *pc; // pointer to program counter reg
    
    Word32_t instr;
    Decoded_instr_t dinstr;
    
    // make sure we were passed a MIPS binary file
    if (argc < 2) {
        ERR_PRINT("We are having a bad problem and you will not go to space today.\n");
        exit(1);
    }

    // begin init routines
    Process_t *proc = build_process();
    if (proc == NULL || proc->reg_file == NULL || proc->mem_space == NULL) {
        ERR_PRINT("Could not build process... crashing\n");
        cleanup(NULL, proc);   
    }
    Arch_info_t *arch = arch_init();
    if (arch == NULL || arch->opcode_table == NULL) {
        ERR_PRINT("Could not build arch info... crashing\n");
        cleanup(arch, proc);   
    }
    if (load_mips_object_file(argv[BIN_FILE_NAME], proc, START_ADDR)) {
        ERR_PRINT("failed to load object file");
        cleanup(arch, proc);
        exit(1);
    }
    
    pc = &(proc->reg_file->pc);

    // main exec loop
    while (FALSE == proc->terminate) {
        DEBUG_PRINT("\n");
        instr = proc->mem_space->memory[START_ADDR + *pc];
        if (0 != instr) { // ensure not NOOP
            dinstr = decode_instr(instr);
            arch->opcode_table->opcodes[dinstr.opcode](dinstr, proc);
        }
    }
    
    cleanup(arch, proc);
    return 0;
}

int load_mips_object_file(char *fname, Process_t *proc, uint32_t addr_offset) {
    FILE *file = fopen(fname, "rb");
    long fsize = -1;
    size_t result;
    
    // sanity check params
    if (fname == NULL || proc == NULL) {
        ERR_PRINT("null args\n");
        return ERR_INVALID_ARGS;
    }
    if (addr_offset >= MEM_SIZE_IN_WORDS) {
        ERR_PRINT("addr_offset %d too large\n", addr_offset);
        return ERR_INVALID_ARGS;
    }
    
    if (file == NULL) {
        ERR_PRINT("Failed to open %s\n", fname);
        return ERR_CANT_OPEN_FILE;
    }
    
    // get file size and check if we have enough space
    fseek(file, 0, SEEK_END);
    fsize = ftell(file);
    if (fsize == -1) {
        ERR_PRINT("Failed to read file size\n");
        return ERR_FILE;
    }
    if ((unsigned long) fsize >= (proc->mem_space->mem_words * proc->mem_space->word_size_bytes - addr_offset)) {
        ERR_PRINT("File too large, not enough space in memory\n");
        fclose(file);
        return ERR_FILE_TOO_LARGE;
    } else if ((unsigned long) fsize > (proc->mem_space->mem_words * proc->mem_space->word_size_bytes) / 4) {
        WARN_PRINT("file occupies more than 1/4 of memory\n");
    }
    rewind(file);
    
    // copy file contents into proc mem space
    result = fread(proc->mem_space->memory + addr_offset, 1, fsize, file);
    if (result != fsize) {
        ERR_PRINT("Couldn't read file %s\n", fname);
        fclose(file);
        return ERR_FILE_READ;
    }
    
    fclose(file);
    return 0;
}
