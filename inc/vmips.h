#pragma once

#include <stdint.h>
#include "debug.h"
#include "errors.h"

#define TRUE 1
#define FALSE 0

/*
 * enums for defining endian-ness
 */
#define VMIPS_BIG_ENDIAN 0
#define VMIPS_LITTLE_ENDIAN 1

/*
 * enums for determining word size and instruction size
 */
#define EIGHT_BIT 8
#define SIXTEEN_BIT 16
#define THIRTY_TWO_BIT 32
#define SIXTY_FOUR_BIT 64

typedef uint32_t Word32_t;

#define BIN_FILE_NAME 1

/*
 * System print and read functions for I/O from within the VM
 */
#define VMIPS_PRINT(...) fprintf(stdout, __VA_ARGS__);
#define VMIPS_READ(...) fscanf(stdin, __VA_ARGS__);