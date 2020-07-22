//
// Created by Andrei Petridean on 6/10/20.
//

#include "headers/branch.h"

/* Gets suffix from given string */
static uint32_t get_suffix(char *suffix) {
    uint32_t result = al;
    if (!strcmp(suffix, "beq")) {
        result = eq;
    } else if (!strcmp(suffix, "bne")) {
        result = ne;
    } else if (!strcmp(suffix, "bge")) {
        result = ge;
    } else if (!strcmp(suffix, "bgt")) {
        result = gt;
    } else if (!strcmp(suffix, "ble")) {
        result = le;
    } else if (!strcmp(suffix, "blt")) {
        result = lt;
    }
    return result;
}

/* Gets the address of the label given in line */
static uint32_t get_address(instr_state_t *state, char *line) {
    uint32_t result = 0;

    /* Counts the previous branch instructions */
    for (int i = 0; i < state->current_instr - 1; i++) {
        if (state->full_instr[i][0] == 'b') {
            result += INCREMENT_PC;
        }
    }

    /* Searches for the label in keywords and returns its address */
    for (int i = 0; i < state->instr_count; i++) {
        if (!strcmp(line, state->keywords[i])) {
            return result + INCREMENT_PC * i;
        }
    }
    return 0;
}

/* Converts branch type instruction to hex */
void branch(instr_state_t *state) {
    /* Initialises utils */
    char *line = calloc(1, sizeof(char));
    if(!line){
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(line, state->full_instr[state->current_instr]);
    uint32_t suffix = get_suffix(
            state->keywords[state->current_instr]);
    char *line_copy = line;
    line = strtok(line, " ");
    line = strtok(NULL, " ");
    uint32_t address = get_address(state, line);
    uint32_t offset = 0;

    /* Checks if the label address is before the current instruction */
    if (address < INCREMENT_PC * state->current_instr + PC_OFFSET) {
        offset += INCREMENT_PC;
    }
    /* Computes offset */
    offset +=
            address - INCREMENT_PC * state->current_instr -
            PC_OFFSET;

    free(line_copy);

    /* Adds instruction to hex_format */
    state->hex_format[state->current_instr] =
            (suffix << BITS_28) | (BRANCH_STD << BITS_25) |
            ((offset >> OFFSET_SHIFT) & OFFSET_MASK);
}
