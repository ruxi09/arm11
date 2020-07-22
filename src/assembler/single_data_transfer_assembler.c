//
// Created by crist on 6/11/2020.
//

#include <stdbool.h>
#include "headers/single_data_transfer_assembler.h"
#include "headers/data_processing.h"

/* Converts single data transfer type instruction to hex */
void single_data_transfer(instr_state_t *state) {
    /* Initialises utils */
    char *line = calloc(1, sizeof(char));
    if (!line) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(line, state->full_instr[state->current_instr],
            strlen(state->full_instr[state->current_instr]));
    char *copy = line;
    char *line_copy = calloc(1, sizeof(char));
    if (!line_copy) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(line_copy, line, strlen(line));
    char *ptr;

    /* Initialises instruction fragments */
    uint32_t rn = 0;
    uint32_t operand2 = 0;
    uint32_t imm = 0;
    uint32_t p = 0;
    uint32_t cond = COND;
    int u = 1;
    uint32_t l = 1;
    /* Sets L bit (load/store) */
    if (line[0] == 's') {
        l = 0;
    }

    /* Computes destination register */
    line = strtok_r(line, " ,#\n", &ptr);
    line = strtok_r(NULL, " ,#\n", &ptr);
    uint32_t rd = get_reg(line);

    /* Modifies line to represent operand2 */
    line = strtok_r(NULL, "\n", &ptr);
    int i, shift = 1;
    if (line[0] == ' ') {
        shift = 2;
    }
    if (line[0] != '=') {
        for (i = 0; i < strlen(line); i++) {
            line[i] = line[i + shift];
        }
    }

    bool has_offset = false; // for the case when operand2 > 0xFF
    if (line[0] != 'r') {
        /* Operand2 is an immediate value*/

        /*Computes operand2 */
        operand2 = compute_operand(line);
        if ((operand2) > 0xff) {
            state->instr_count++;
            p = 1;
            imm = 0;
            rn = PC;
            state->hex_format[state->instr_count - 1] = operand2;
            has_offset = true;
        } else {
            /* It treats load as mov (data_processing) */
            state->full_instr[state->current_instr][0] = 'm';
            state->full_instr[state->current_instr][1] = 'o';
            state->full_instr[state->current_instr][2] = 'v';

            /* Change '=' to '#' to reassemble a mov format */
            int pos = 3;
            while (state->full_instr[state->current_instr][pos] !=
                   '=') {
                pos++;
            }
            state->full_instr[state->current_instr][pos] = '#';

            data_processing(state);

            free(line_copy);
            free(copy);
            return;
        }
    } else {
        /* Operand2 is not an immediate value */
        char *str[4];
        str[0] = strtok_r(line, "]", &ptr);
        str[1] = strtok_r(NULL, "], ", &ptr);
        str[2] = strtok_r(NULL, "], ", &ptr);
        str[3] = strtok_r(NULL, "], #", &ptr);

        /* Computes operand2 and decides if it is immediate or not */
        imm = 1;
        if (str[1] == NULL) {
            p = 1;
            str[0] = strtok_r(str[0], ", #", &ptr);
            str[1] = strtok_r(NULL, ", ", &ptr);
            str[2] = strtok_r(NULL, "], ", &ptr);
            str[3] = strtok_r(NULL, "], #", &ptr);
            if (str[1] != NULL) {
                if (str[1][0] == 'r') {
                    imm = 0;
                }
                if (str[1][1] == '-') {
                    u = 0;
                }
                operand2 = compute_operand(str[1]);
            }
        } else {
            p = 0;
            operand2 = compute_operand(str[1]);
            imm = 0;
        }

        /* Computes the base register */
        rn = get_reg(str[0]);

        /* Decides if the operand is subtracted from the register */
        if (str[1] != NULL && str[2] != NULL) {
            if (str[1][1] == '-') {
                u = 0;
            }
        }


    }

    free(line_copy);
    free(copy);

    /* Adds instruction to hex_format depending if it has an offset or not */
    if (has_offset) {
        uint32_t offset =
                ((state->instr_count - 1) - state->current_instr) *
                4 -
                PC_OFFSET;
        state->hex_format[state->current_instr] =
                (cond << BITS_28) | (1 << BITS_26) | (imm << BITS_25) | p << P |
                (u ? U : 0) | (l << BITS_20) | (rn << BITS_16) |
                (rd << BITS_12) |
                (offset);
    } else {
        state->hex_format[state->current_instr] =
                (cond << BITS_28) | (1 << BITS_26) | ((imm == 0) << BITS_25) |
                p << P |
                (u ? U : 0) | (l << BITS_20) | (rn << BITS_16) |
                (rd << BITS_12) |
                (operand2);
    }
}
