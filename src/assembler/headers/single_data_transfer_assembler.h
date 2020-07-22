//
// Created by crist on 6/11/2020.
//

#ifndef ARM11_10_SINGLE_DATA_TRANSFER_ASSEMBLER_H
#define ARM11_10_SINGLE_DATA_TRANSFER_ASSEMBLER_H
#include "./assembler_utils.h"
#define COND 14
#define PC 15
#define PC_OFFSET 8
#define P 24
#define BITS_26 26
#define BITS_12 12
#define BITS_28 28
#define BITS_20 20
#define BITS_16 16
#define BITS_25 25
#define U 1 << 23

/* Converts single data transfer type instruction to hex */
void single_data_transfer(instr_state_t *state);

#endif //ARM11_10_SINGLE_DATA_TRANSFER_ASSEMBLER_H
