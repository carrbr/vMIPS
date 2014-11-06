#pragma once

#include "hardware.h"

typedef struct {
    Reg_file_t *reg_file;
    Memory_t *mem_space;
} Process_t;

Process_t *build_process();
