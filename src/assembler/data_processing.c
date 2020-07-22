//
// Created by Andrei Petridean on 6/12/20.
//

#include <stdbool.h>
#include "headers/data_processing.h"

/* Computes the cond bits for given opcode */
static Opcode get_opcode_info(char *keyword) {
    Opcode result;
    if (!strcmp(keyword, "and")) {
        result = and;
    } else if (!strcmp(keyword, "eor")) {
        result = eor;
    } else if (!strcmp(keyword, "sub")) {
        result = sub;
    } else if (!strcmp(keyword, "rsb")) {
        result = rsb;
    } else if (!strcmp(keyword, "add")) {
        result = add;
    } else if (!strcmp(keyword, "orr")) {
        result = orr;
    } else if (!strcmp(keyword, "mov") || !strcmp(keyword, "lsl")) {
        result = mov;
    } else if (!strcmp(keyword, "tst")) {
        result = tst;
    } else if (!strcmp(keyword, "teq")) {
        result = teq;
    } else if (!strcmp(keyword, "cmp")) {
        result = cmp;
    } else {
        perror("opcode invalid");
        exit(EXIT_FAILURE);
    }

    return result;
}

/* Performs rotation */
static uint32_t rotate(uint32_t number) {
    /* Initialises utils */
    uint32_t rot;
    uint32_t result = number;
    bool cond = true;
    int rotate_value = 0;

    while (cond) {
        /* Masks last two bits */
        int bit0 = (number & 1);
        int bit1 = ((number & 2) >> 1);

        /* Checks if any is on */
        if ((bit0) || (bit1)) {
            cond = false;
        } else {
            /* Performs another rotation */
            number = number >> ROTATE_SHIFT_AMOUNT;
            rotate_value++;
        }
    }

    /* Computes result */
    if (rotate_value != 0) {
        rot = (uint32_t) (INSTR_MID - rotate_value);
        result = (number & LAST_TWO_BYTES_MASK) | (rot << SHIFT_TWO_BYTES);
    }
    return result;
}

/* Converts data processing type instruction to hex */
void data_processing(instr_state_t *state) {
    /* Initialises utils */
    char *line = calloc(1, sizeof(char));
    if(!line){
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(line, state->full_instr[state->current_instr],
            strlen(state->full_instr[state->current_instr]));
    char *curr_word = calloc(1, sizeof(char));
    if(!curr_word){
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    char *curr_word_copy = curr_word;
    strncpy(curr_word, line, strlen(line));
    curr_word = strtok(curr_word, " ");

    /* Initialises instruction fragments */
    uint32_t S = 0;
    uint32_t rn = 0;
    uint32_t rd = 0;
    uint32_t cond = COND_DP;
    uint32_t I = strchr(line, '#') ? 1 : 0;
    uint32_t operand2;

    /* Handles operand2 */
    if (!strcmp(state->keywords[state->current_instr], "lsl")) {
        I = 0;
        operand2 = compute_operand(line);
        operand2 = (operand2 << OPERAND2_SHIFT_NOT_IMM) | 1;
    } else {
        operand2 = compute_operand(line);
        if (operand2 > LAST_TWO_BYTES_MASK) {
            operand2 = rotate(operand2);
        }
    }

    /* Computes opcode */
    Opcode ins_op = get_opcode_info(curr_word);
    uint32_t opcode = ins_op;

    /* Computes register depending on opcode */
    switch (ins_op) {
        case and :
        case eor :
        case orr :
        case sub :
        case rsb :
        case add :
            curr_word = strtok(NULL, " ,#");
            rd = get_reg(curr_word);
            curr_word = strtok(NULL, " ,#");
            rn = get_reg(curr_word);
            break;
        case tst :
        case teq :
        case cmp :
            S = 1;
            curr_word = strtok(NULL, " ,#");
            rn = get_reg(curr_word);
            break;
        case mov :
            curr_word = strtok(NULL, " ,#");
            rd = get_reg(curr_word);
            break;

    }

    /* Shifts instruction fragments to correct position */
    cond = cond << COND_MASK_DP;
    I = I << I_MASK_DP;
    opcode = opcode << OPCODE_MASK_DP;
    S = S << S_MASK_DP;
    rn = rn << RN_MASK_DP;
    rd = rd << RD_MASK_DP;

    free(curr_word_copy);
    if (line) {
        free(line);
    }

    /* Adds instruction to hex_format */
    state->hex_format[state->current_instr] =
            cond | I | opcode | S | rn | rd | operand2;
}
