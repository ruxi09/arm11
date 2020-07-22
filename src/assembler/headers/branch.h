//
// Created by Andrei Petridean on 6/10/20.
//

#ifndef ARM11_10_BRANCH_H
#define ARM11_10_BRANCH_H

#include "./assembler_utils.h"

#define PC_OFFSET 8
#define BITS_28 28
#define BITS_25 25
#define OFFSET_MASK 0xffffff
#define OFFSET_SHIFT 2
#define BRANCH_STD 5 // 101 in binary

/* Converts branch type instruction to hex */
void branch(instr_state_t *state);

#endif //ARM11_10_BRANCH_H
