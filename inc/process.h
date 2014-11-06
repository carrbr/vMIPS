#pragma once

#include "arch.h"

typedef struct {
    Reg_file_t *reg_file;
    int num_regs;
    Memory_t *mem_space;
} Process_t;

Process_t *build_process();