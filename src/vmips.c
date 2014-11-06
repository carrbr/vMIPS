#include <stdio.h>
#include "vmips.h"
#include "process.h"
#include "hardware.h"

int main() {

}

Arch_info_t *init() {
    // get info from implementation about the architecture we are simulating
    Arch_info_t *arch_config = (Arch_info_t *)arch_init();
    return arch_config;
}

Process_t *build_process() {    
    // setup environment for code execution
    Process_t *proc = malloc(sizeof(Process_t));
    proc->reg_file = init_reg_file();
    proc->mem_space = init_memory_space();
    return proc;
}
