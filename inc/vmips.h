#pragma once

#include <stdint.h>

#define TRUE 1
#define FALSE 0

/*
 * enums for defining endian-ness
 */
#define BIG_ENDIAN 0
#define LITTLE_ENDIAN 1

/*
 * enums for determining word size and instruction size
 */
#define EIGHT_BIT 8
#define SIXTEEN_BIT 16
#define THIRTY_TWO_BIT 32
#define SIXTY_FOUR_BIT 64

typedef struct {
    int endian;
    int wordsize;
    int instr_length;
} Arch_info_t;

typedef uint32_t Word32_t;
