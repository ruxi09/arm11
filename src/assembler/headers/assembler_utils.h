//
// Created by Andrei Petridean on 6/12/20.
//

#ifndef ARM11_10_ASSEMBLER_UTILS_H
#define ARM11_10_ASSEMBLER_UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../structures.h"

#define HEX_ID_POS 2
#define HEX_BASE 16
#define DEC_BASE 10

/* Computes operand2 given a line of code */
uint32_t compute_operand(char* line);

/* Computes register given a char array */
uint32_t get_reg(char *reg_string);


#endif //ARM11_10_ASSEMBLER_UTILS_H
