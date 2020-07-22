//
// Created by Andrei Petridean on 6/12/20.
//

#include "headers/multiply.h"

/* Converts multiply type instruction to hex */
void multiply(instr_state_t *state) {
    /* Initialises utils */
    char *line = calloc(1, sizeof(char));
    if (!line) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(line, state->full_instr[state->current_instr],
            strlen(state->full_instr[state->current_instr]));

    /*Initialises instruction fragments */
    uint32_t rd;
    uint32_t rs;
    uint32_t rm;
    uint32_t rn = 0;
    uint32_t A = 0;
    uint32_t S = 0;
    uint32_t cond = COND_MUL;
    uint32_t bit4_7 = MUL_STD;

    char *curr_word = calloc(1, sizeof(char));
    if (!curr_word) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    /* Creates copy to avoid memory leaks */
    char *curr_word_copy = curr_word;

    /* Computes registers */
    strncpy(curr_word, line, strlen(line));
    curr_word = strtok(curr_word, " ,");
    curr_word = strtok(NULL, " ,");
    rd = get_reg(curr_word);
    curr_word = strtok(NULL, " ,");
    rm = get_reg(curr_word);
    curr_word = strtok(NULL, " ,");
    rs = get_reg(curr_word);

    /* Handles mla case */
    if (!strcmp("mla", state->keywords[state->current_instr])) {
        A = 1;
        curr_word = strtok(NULL, " ,");
        rn = get_reg(curr_word);
    }

    /* Shifts instruction fragments to correct position */
    cond = cond << COND_MASK_MUL;
    A = A << A_MASK_MUL;
    S = S << S_MASK_MUL;
    rn = rn << RN_MASK_MUL;
    rd = rd << RD_MASK_MUL;
    bit4_7 = bit4_7 << MASK_4_7_MUL;
    rs = rs << RS_MASK_MUL;

    free(line);
    free(curr_word_copy);

    /* Adds instruction to hex_format */
    state->hex_format[state->current_instr] =
            cond | A | S | rn | rd | bit4_7 | rs | rm;
}
