//
// Created by Andrei Petridean on 6/12/20.
//

#include "headers/assembler_utils.h"

/* Computes operand2 given a line of code */
uint32_t compute_operand(char *line) {
    /* Initialising utils */
    char *p1;
    uint32_t operand2 = 0;
    char *last_word = calloc(1, sizeof(char));
    if(!last_word){
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(last_word, line, strlen(line));
    int pos = strlen(last_word) - 1;

    /* Checks if operand is negative */
    char *negative = strchr(last_word, '-');
    if (negative) {
        strcpy(negative, negative + 1);
    }

    /* Computes the position of the last word */
    while (last_word[pos] != ' ' && last_word[pos] != ',' && pos > 0) {
        pos--;
    }

    /* if the last word is not also the first word, it eliminates the delimiter */
    if (last_word[pos] == ' ' || last_word[pos] == ',') {
        strcpy(last_word, last_word + pos + 1);
    }

    /* Makes a copy of last_word to avoid memory leaks */
    char *last_word_copy = last_word;

    if (last_word[0] == 'r') {
        /* Operand is a register */
        operand2 = atoi(strtok_r(last_word, "-r", &p1));
    } else if (strlen(last_word) > HEX_ID_POS && last_word[HEX_ID_POS] == 'x') {
        /* Operand is in hex format */
        strcpy(last_word, last_word + HEX_ID_POS + 1);
        while (last_word[0] != '\0') {
            if (last_word[0] >= '0' && last_word[0] <= '9') {
                operand2 = operand2 * HEX_BASE + (last_word[0] - '0');
            } else if (last_word[0] >= 'A' && last_word[0] <= 'F') {
                operand2 =
                        operand2 * HEX_BASE + (DEC_BASE + last_word[0] - 'A');
            } else {
                operand2 =
                        operand2 * HEX_BASE + (DEC_BASE + last_word[0] - 'a');
            }
            strcpy(last_word, last_word + 1);
        }
    } else {
        /* Operand is in dec format */
        last_word = last_word + 1;
        while (last_word[0] != '\0') {
            operand2 = operand2 * DEC_BASE + (last_word[0] - '0');
            strcpy(last_word, last_word + 1);
        }
    }

    free(last_word_copy);
    return operand2;
}

/* Computes register given a char array */
uint32_t get_reg(char *reg_string) {

    uint32_t reg;

    reg = reg_string[1] - '0';

    if (reg_string[2] != '\0') {
        reg = reg * DEC_BASE + (reg_string[2] - '0');
    }

    return reg;

}