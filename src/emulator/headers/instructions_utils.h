//
// Created by Ruxi on 28/05/2020.
//


#ifndef ARM11_10_INSTRUCTIONS_UTILS_H
#define ARM11_10_INSTRUCTIONS_UTILS_H

#include "../../structures.h"

/* USEFUL VALUES */
#define MAX 0xFFFFFFFF
#define MAX_BITS 32
#define MSB 31
#define SHIFT_AMOUNT 31
#define PC_ADDRESS 15
#define PC_OFFSET 8

/* MASKS */
#define MASK_BIT_31 0x80000000
#define MASK_BIT_0 0x00000001
#define MASK_IMMEDIATE 0x000000FF
#define MASK_ROTATE 0x00000F00

/* FOR SHIFT */
#define SHIFT_ROTATE 8
#define BYTES_PER_WORD 4
#define BITS_PER_BYTE 8
#define RM_START 0
#define RM_END 4
#define SHIFT_START 7
#define SHIFT_END 12
#define OPT_SHIFT_AMOUNT_START 8
#define OPT_SHIFT_AMOUNT_END 12
#define SHIFT_T_START 5
#define SHIFT_T_END 7

/* BITS POSITIONS */
#define N_BIT 31
#define Z_BIT 30
#define C_BIT 29
#define V_BIT 28
#define I_BIT 25
#define S_BIT 20
#define A_BIT 21
#define P_BIT 24
#define U_BIT 23
#define L_BIT 20
#define OP_REG_BIT 4

/* FOR DECODING: */
#define COND_START 28
#define COND_END 32
#define OPCODE_START 21
#define OPCODE_END 25
#define OPERAND2_START 0
#define OPERAND2_END 12
#define RN_START 16
#define RN_END 20
#define RD_START 12
#define RD_END 16
#define SDT_OFFSET_START 0
#define SDT_OFFSET_END 12
#define BR_OFFSET_START 0
#define BR_OFFSET_END 24

/* FOR DECODING MULTIPLY */
#define RS_START 8
#define RS_END 12

/* Function to get bits between start and end: */
uint32_t get(uint32_t value, int begin, int end);

/* Retrieves instruction pointed by PC: */
uint32_t get_instruction(State *current_state);

/* FUNCTIONS FOR SETTING THE C FLAG: */
/* For and, eor, orr, teq, tst, mov */
void set_C(State *current_state, int carry_out);

/* For add */
void
set_C_add(State *current_state, uint32_t first_value, uint32_t second_value);

/* For sub, cmp, rsb */
void
set_C_sub(State *current_state, uint32_t first_value, uint32_t second_value);

/* FUNCTION FOR SETTING BOTH N AND Z FLAGS: */
void set_N_Z(State *current_state, uint32_t result);

/* Returns shift result of rotation */
Shift_result rotate(int shift_value, uint32_t rm_value);

/* To get immediate value: */
uint32_t immediate(int rotate_value, uint32_t imm_value);

/* Checks if COND is satisfied by CPSR */
int check_cond(State *current_state);

/* Executes shift */
Shift_result shift(State *current_state);

/* Loads instruction from memory */
uint32_t load(State *current_state, uint32_t address);

/* Stores instruction to memory */
void store(State *current_state, uint32_t address, uint32_t value);

/* Performs GIPO checks */
int is_GPIO(uint32_t address);

#endif //ARM11_10_INSTRUCTIONS_UTILS_H
