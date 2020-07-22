//
// Created by nicol on 27/05/2020.
//

#ifndef ARM11_10_UTILS_H
#define ARM11_10_UTILS_H

#include <stdio.h>

/* Transforms value from big endian to little endian */
uint32_t reverse(uint32_t value);

/* Frees allocated memory */
void free_state(State *current_state);

/* Gets input file and checks arguments and path are correct*/
FILE *get_file(FILE *input, int argc, char *path, State *current_state);

/* Reads from input */
void read(FILE *input, State *current_state);

void initialise_registers(State *current_state);

void print_registers(State *current_state);

void print_memory(State *current_state);

#endif //ARM11_10_UTILS_H
