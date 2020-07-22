//
// Created by Andrei Petridean on 6/12/20.
//

#ifndef ARM11_10_DATA_PROCESSING_H
#define ARM11_10_DATA_PROCESSING_H


#include "./assembler_utils.h"
#define COND_DP 0x0000000E
#define COND_MASK_DP 28
#define I_MASK_DP 25
#define OPCODE_MASK_DP 21
#define S_MASK_DP 20
#define RN_MASK_DP 16
#define RD_MASK_DP 12
#define ROTATE_SHIFT_AMOUNT 2
#define INSTR_MID 16
#define LAST_TWO_BYTES_MASK 0xFF
#define SHIFT_TWO_BYTES 8
#define OPERAND2_SHIFT_NOT_IMM 7


/* Converts data processing type instruction to hex */
void data_processing(instr_state_t *state);


#endif //ARM11_10_DATA_PROCESSING_H
