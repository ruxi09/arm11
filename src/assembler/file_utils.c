//
// Created by Ruxi on 10/06/2020.
//

#include "headers/file_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MASK_SECOND_BYTE 0x00ff0000
#define MASK_THIRD_BYTE 0x0000ff00
#define SHIFT_ONE_BYTE 8
#define SHIFT_THREE_BYTES 24

/* Creates a 2d array of chars */
static char **create_2d_array(unsigned int rows, unsigned int cols) {
    unsigned int i;
    char **loaded_file = calloc(rows, sizeof(char *));
    if (!loaded_file) {
        perror("Error allocating memory for source file");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < rows; i++) {
        loaded_file[i] = calloc(cols, sizeof(char));
        if (!loaded_file[i]) {
            perror("Error allocating memory for source file");
            exit(EXIT_FAILURE);
        }
    }
    return loaded_file;
}

/* Computes the number of lines in input file */
static int file_lines(char *filename) {
    FILE *file;
    int count = 0;  // Line counter (result)
    char c;  // To store a character read from file

    file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') {
            count = count + 1;
        }
    }

    fclose(file);
    return count;
}

/* Loads file and adds full instructions to state */
void load_file(char *filename, instr_state_t *state) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error in opening source file");
        exit(EXIT_FAILURE);
    }

    //Set up the correct size array;
    int lines = file_lines(filename);
    state->full_instr = create_2d_array(lines, LINE_MAX);

    // Try to read the file line by line
    int size = 0;
    while (size < lines && fgets(state->full_instr[size], LINE_MAX, file)) {
        if (state->full_instr[size][0] != '\n' &&
            state->full_instr[size][0] != '\r') {
            state->full_instr[size][strcspn(state->full_instr[size], "\n")] = 0;
            size++;
        }
    }
    state->instr_count = size;
    fclose(file);
}

/* Gets the keywords from each line of assembly */
/* By "keywords", we mean the first word from a line (mnemonic or label) */
void get_keywords(instr_state_t *state) {
    state->keywords = create_2d_array(state->instr_count, LINE_MAX);
    for (int i = 0; i < state->instr_count; i++) {
        strcpy(state->keywords[i], state->full_instr[i]);
        state->keywords[i] = strtok(state->keywords[i], " :");
    }
}

/* Binary file writer (writes from state->hex_format) */
void write_file(char *filename, instr_state_t *state) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("File does not exist.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < state->instr_count; i++) {
        if (!(state->hex_format[i] == 0 && strchr(state->full_instr[i], ':'))) {
            fwrite(&state->hex_format[i], sizeof(int), 1, file);
        }
    }

    fclose(file);
}


