//
// Created by Andrei Petridean on 6/12/20.
//

#ifndef ARM11_10_MULTIPLY_H
#define ARM11_10_MULTIPLY_H
#include "./assembler_utils.h"

#define MUL_STD 9
#define COND_MUL 0x0000000E
#define COND_MASK_MUL 28
#define A_MASK_MUL 21
#define S_MASK_MUL 20
#define RN_MASK_MUL 12
#define RD_MASK_MUL 16
#define MASK_4_7_MUL 4
#define RS_MASK_MUL 8

/* Converts multiply type instruction to hex */
void multiply(instr_state_t *state);


#endif //ARM11_10_MULTIPLY_H
