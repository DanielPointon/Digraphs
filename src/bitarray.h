/********************************************************************************
**
*A  bitarray.h               bit arrays                           J. D. Mitchell
**
**  Copyright (C) 2019 - J. D. Mitchell
**
**  This file is free software, see the digraphs/LICENSE.
**
********************************************************************************/

#ifndef DIGRAPHS_SRC_BITARRAY_H_
#define DIGRAPHS_SRC_BITARRAY_H_

// C headers
#include <limits.h>   // for CHAR_BIT
#include <stdbool.h>  // for bool
#include <stddef.h>   // for size_t
#include <stdint.h>   // for uint16_t
#include <string.h>   // for memset

// GAP headers
#include "gap-includes.h"  // for COUNT_TRUES_BLOCKS, Obj, . . .

// Digraphs headers
#include "digraphs-debug.h"  // for DIGRAPHS_ASSERT

typedef UInt Block;

#define NUMBER_BITS_PER_BLOCK (sizeof(Block) * CHAR_BIT)

#ifndef MAXVERTS
#define MAXVERTS 512
#endif

#if SYS_IS_64_BIT
// To avoid division and mod
static size_t const NR_BLOCKS_LOOKUP[MAXVERTS + 1] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

static size_t const REMAINDER[MAXVERTS + 1] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
    57, 58, 59, 60, 61, 62, 63, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 0,  1,  2,  3,  4,
    5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
    43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
    62, 63, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
    55, 56, 57, 58, 59, 60, 61, 62, 63, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 0,  1,  2,
    3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 0,  1,  2,  3,  4,  5,  6,  7,
    8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
    27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 0};

static size_t const QUOTIENT[MAXVERTS + 1] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8};

static const Block MASK[NUMBER_BITS_PER_BLOCK] = {0x1,
                                                  0x2,
                                                  0x4,
                                                  0x8,
                                                  0x10,
                                                  0x20,
                                                  0x40,
                                                  0x80,
                                                  0x100,
                                                  0x200,
                                                  0x400,
                                                  0x800,
                                                  0x1000,
                                                  0x2000,
                                                  0x4000,
                                                  0x8000,
                                                  0x10000,
                                                  0x20000,
                                                  0x40000,
                                                  0x80000,
                                                  0x100000,
                                                  0x200000,
                                                  0x400000,
                                                  0x800000,
                                                  0x1000000,
                                                  0x2000000,
                                                  0x4000000,
                                                  0x8000000,
                                                  0x10000000,
                                                  0x20000000,
                                                  0x40000000,
                                                  0x80000000,
                                                  0x100000000,
                                                  0x200000000,
                                                  0x400000000,
                                                  0x800000000,
                                                  0x1000000000,
                                                  0x2000000000,
                                                  0x4000000000,
                                                  0x8000000000,
                                                  0x10000000000,
                                                  0x20000000000,
                                                  0x40000000000,
                                                  0x80000000000,
                                                  0x100000000000,
                                                  0x200000000000,
                                                  0x400000000000,
                                                  0x800000000000,
                                                  0x1000000000000,
                                                  0x2000000000000,
                                                  0x4000000000000,
                                                  0x8000000000000,
                                                  0x10000000000000,
                                                  0x20000000000000,
                                                  0x40000000000000,
                                                  0x80000000000000,
                                                  0x100000000000000,
                                                  0x200000000000000,
                                                  0x400000000000000,
                                                  0x800000000000000,
                                                  0x1000000000000000,
                                                  0x2000000000000000,
                                                  0x4000000000000000,
                                                  0x8000000000000000};
#else
static size_t const NR_BLOCKS_LOOKUP[MAXVERTS + 1] = {
    0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
    3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
    3,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5,
    5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
    5,  5,  5,  5,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
    6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
    6,  6,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  9,  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};

static size_t const REMAINDER[MAXVERTS + 1] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,  4,  5,
    6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,  4,
    5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,
    4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
    29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,
    3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,
    9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
    28, 29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,
    2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,
    8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
    27, 28, 29, 30, 31, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0};

static size_t const QUOTIENT[MAXVERTS + 1] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
    3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,
    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    4,  4,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
    5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
    5,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
    6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
    9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16};

static const Block MASK[NUMBER_BITS_PER_BLOCK] = {
    0x1,        0x2,       0x4,       0x8,       0x10,       0x20,
    0x40,       0x80,      0x100,     0x200,     0x400,      0x800,
    0x1000,     0x2000,    0x4000,    0x8000,    0x10000,    0x20000,
    0x40000,    0x80000,   0x100000,  0x200000,  0x400000,   0x800000,
    0x1000000,  0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000,
    0x40000000, 0x80000000};

#endif

struct bit_array_struct {
  uint16_t nr_bits;    // number of bits
  uint16_t nr_blocks;  // number of blocks
  Block*   blocks;     // the blocks themselves
};

typedef struct bit_array_struct BitArray;

//! New BitArray with space for \p nr_bits bits, and with every bit set to \c
//! false.
BitArray* new_bit_array(uint16_t const nr_bits);

//! Free all the memory associated with a BitArray false.
void free_bit_array(BitArray* const);

//! Set every value in the BitArray pointed to by \p bit_array to the value \p
//! val.
static inline void init_bit_array(BitArray* const bit_array,
                                  bool const      val,
                                  uint16_t const  nr_bits) {
  DIGRAPHS_ASSERT(bit_array != NULL);
  DIGRAPHS_ASSERT(nr_bits <= bit_array->nr_bits);
  uint16_t const nr_blocks = NR_BLOCKS_LOOKUP[nr_bits];
  if (val) {
    memset((void*) bit_array->blocks, ~0, (size_t) sizeof(Block) * nr_blocks);
  } else {
    memset((void*) bit_array->blocks, 0, (size_t) sizeof(Block) * nr_blocks);
  }
}

//! Set position \p pos in the BitArray pointed to by \p bit_array
//! to the value \p val.
static inline void
set_bit_array(BitArray* const bit_array, uint16_t const pos, bool const val) {
  DIGRAPHS_ASSERT(bit_array != NULL);
  DIGRAPHS_ASSERT(pos < bit_array->nr_bits);
  if (val) {
    bit_array->blocks[QUOTIENT[pos]] |= MASK[REMAINDER[pos]];
  } else {
    bit_array->blocks[QUOTIENT[pos]] &= ~MASK[REMAINDER[pos]];
  }
}

//! Get the value in position \p pos of the BitArray pointer
//! \p bit_array.
static inline bool get_bit_array(BitArray const* const bit_array,
                                 uint16_t const        pos) {
  DIGRAPHS_ASSERT(bit_array != NULL);
  DIGRAPHS_ASSERT(pos < bit_array->nr_bits);
  return bit_array->blocks[QUOTIENT[pos]] & MASK[REMAINDER[pos]];
}

//! Intersect the BitArray's pointed to by \p bit_array1 and \p bit_array2. The
//! BitArray pointed to by \p bit_array1 is changed in place!
static inline void intersect_bit_arrays(BitArray* const       bit_array1,
                                        BitArray const* const bit_array2,
                                        uint16_t const        nr_bits) {
  DIGRAPHS_ASSERT(bit_array1 != NULL);
  DIGRAPHS_ASSERT(bit_array2 != NULL);
  DIGRAPHS_ASSERT(bit_array1->nr_bits == bit_array2->nr_bits);
  DIGRAPHS_ASSERT(bit_array1->nr_blocks == bit_array2->nr_blocks);
  DIGRAPHS_ASSERT(nr_bits <= bit_array1->nr_bits);
  DIGRAPHS_ASSERT(nr_bits <= bit_array2->nr_bits);
  uint16_t const nr_blocks = NR_BLOCKS_LOOKUP[nr_bits];
  for (uint16_t i = 0; i < nr_blocks; i++) {
    bit_array1->blocks[i] &= bit_array2->blocks[i];
  }
}

//! Union the BitArray's pointed to by \p bit_array1 and \p bit_array2. The
//! BitArray pointed to by \p bit_array1 is changed in place!
static inline void union_bit_arrays(BitArray* const       bit_array1,
                                    BitArray const* const bit_array2,
                                    uint16_t const        nr_bits) {
  DIGRAPHS_ASSERT(bit_array1 != NULL);
  DIGRAPHS_ASSERT(bit_array2 != NULL);
  DIGRAPHS_ASSERT(bit_array1->nr_bits == bit_array2->nr_bits);
  DIGRAPHS_ASSERT(bit_array1->nr_blocks == bit_array2->nr_blocks);
  DIGRAPHS_ASSERT(nr_bits <= bit_array1->nr_bits);
  DIGRAPHS_ASSERT(nr_bits <= bit_array2->nr_bits);
  uint16_t const nr_blocks = NR_BLOCKS_LOOKUP[nr_bits];
  for (uint16_t i = 0; i < nr_blocks; i++) {
    bit_array1->blocks[i] |= bit_array2->blocks[i];
  }
}

//! Sets \p bit_array1 to be 0 in every position that \p bit_array2 is 1.
static inline void complement_bit_arrays(BitArray* const       bit_array1,
                                         BitArray const* const bit_array2,
                                         uint16_t const        nr_bits) {
  DIGRAPHS_ASSERT(bit_array1 != NULL);
  DIGRAPHS_ASSERT(bit_array2 != NULL);
  DIGRAPHS_ASSERT(bit_array1->nr_bits == bit_array2->nr_bits);
  DIGRAPHS_ASSERT(bit_array1->nr_blocks == bit_array2->nr_blocks);
  DIGRAPHS_ASSERT(nr_bits <= bit_array1->nr_bits);
  DIGRAPHS_ASSERT(nr_bits <= bit_array2->nr_bits);
  uint16_t const nr_blocks = NR_BLOCKS_LOOKUP[nr_bits];
  for (uint16_t i = 0; i < nr_blocks; i++) {
    bit_array1->blocks[i] &= ~bit_array2->blocks[i];
  }
}

//! This function copies \p bit_array2 into \p bit_array1
static inline void copy_bit_array(BitArray* const       bit_array1,
                                  BitArray const* const bit_array2,
                                  uint16_t const        nr_bits) {
  DIGRAPHS_ASSERT(bit_array1 != NULL);
  DIGRAPHS_ASSERT(bit_array2 != NULL);
  DIGRAPHS_ASSERT(bit_array1->nr_bits == bit_array2->nr_bits);
  DIGRAPHS_ASSERT(bit_array1->nr_blocks == bit_array2->nr_blocks);
  DIGRAPHS_ASSERT(nr_bits <= bit_array1->nr_bits);
  DIGRAPHS_ASSERT(nr_bits <= bit_array2->nr_bits);
  uint16_t const nr_blocks = NR_BLOCKS_LOOKUP[nr_bits];
  for (uint16_t i = 0; i < nr_blocks; i++) {
    bit_array1->blocks[i] = bit_array2->blocks[i];
  }
}

//! Return the number of set bits among the first \p nr_bits of \p bit_array.
static inline uint16_t size_bit_array(BitArray const* const bit_array,
                                      uint16_t const        nr_bits) {
  DIGRAPHS_ASSERT(bit_array != NULL);
  DIGRAPHS_ASSERT(nr_bits <= bit_array->nr_bits);
  Block const*   blocks    = bit_array->blocks;
  uint16_t const nr_blocks = NR_BLOCKS_LOOKUP[nr_bits];
  return COUNT_TRUES_BLOCKS(blocks, nr_blocks);
}

//! Set the bit array \p bit_array to be \c true in position INT_INTOBJ(o) - 1.
void set_bit_array_from_gap_int(BitArray* const bit_array, Obj o);

//! Set the bit array \p bit_array to be \c true for every integer valyue in
//! \p list_obj (which should be a list consisting of integers, not necessarily
//! plain or dense).
void set_bit_array_from_gap_list(BitArray* const bit_array, Obj list_obj);

#endif  //  DIGRAPHS_SRC_BITARRAY_H_
