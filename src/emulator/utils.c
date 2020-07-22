//
// Created by nicol on 27/05/2020.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../structures.h"
#include "headers/instructions_utils.h"

#define MASK_SECOND_BYTE 0x00ff0000
#define MASK_THIRD_BYTE 0x0000ff00
#define SHIFT_ONE_BYTE 8
#define SHIFT_THREE_BYTES 24

/* Transforms value from big endian to little endian */
uint32_t reverse(uint32_t value) {
    // Assume: value = 0xaabbccdd

    // first  = 0xdd000000
    uint32_t first_byte = value << SHIFT_THREE_BYTES;

    // second = 0x00cc0000
    uint32_t second_byte = (value & MASK_THIRD_BYTE) << SHIFT_ONE_BYTE;

    // third  = 0x0000bb00
    uint32_t third_byte = (value & MASK_SECOND_BYTE) >> SHIFT_ONE_BYTE;

    // fourth = 0x000000aa
    uint32_t fourth_byte = value >> SHIFT_THREE_BYTES;

    return first_byte | second_byte | third_byte | fourth_byte;
}

/* Frees allocated memory */
void free_state(State *current_state) {
    free(current_state->mem);
    free(current_state->regs);
    free(current_state->decoded_part);
    free(current_state);
}

/* Gets input file and checks arguments and path are correct*/
FILE *get_file(FILE *input, int argc, char *path, State *current_state) {
    if (argc != 2) {
        printf("Error: missing/too many arguments \n");
        free_state(current_state);
        exit(EXIT_FAILURE);
    }
    input = fopen(path, "rb");
    if (!input) {
        printf("Error: could not find file in specified path\n");
        free(current_state->mem);
        free_state(current_state);
        exit(EXIT_FAILURE);
    }
    return input;
}

/* Reads from input */
void read(FILE *input, State *current_state) {
    // get the end of the file
    fseek(input, 1, SEEK_END);

    // store the file length
    // we add one in order to include the zero instruction as well
    uint64_t file_length = ftell(input) + 1;

    // goes back to the beginning of file
    rewind(input);
    size_t res = fread(current_state->mem, 1, MEM_CAPACITY, input);
    if (res < MEM_CAPACITY && ferror(input)) {
        free_state(current_state);
        fclose(input);
        exit(EXIT_FAILURE);
    }
    // reverse the bits as ARM is little endian
    for (int i = 0; i < file_length; i++) {
        current_state->mem[i] = reverse(current_state->mem[i]);
    }
}

void initialise_registers(State *current_state) {
    for (int i = 0; i < NO_OF_GENERAL_REGISTERS; i++) {
        current_state->regs->general[i] = 0x0;
    }
    current_state->regs->PC = 0x0;
    current_state->regs->CPSR.C = 0;
    current_state->regs->CPSR.N = 0;
    current_state->regs->CPSR.V = 0;
    current_state->regs->CPSR.Z = 0;
}

/* Converts from struct CPSR (four ints) to value */
int CPSR_convert(State *current_state) {
    int CPSR = 0;
    CPSR |= current_state->regs->CPSR.N << N_BIT |
            current_state->regs->CPSR.Z << Z_BIT
            | current_state->regs->CPSR.C << C_BIT |
            current_state->regs->CPSR.V << V_BIT;
    return CPSR;
}

void print_registers(State *current_state) {
    printf("Registers:\n");
    for (int i = 0; i < NO_OF_GENERAL_REGISTERS; i++) {
        printf("$%-3d", i);
        printf(": %10d (0x%08x)\n",
               current_state->regs->general[i],
               current_state->regs->general[i]);
    }
    printf("PC  : %10d (0x%08x)\n", current_state->regs->PC,
           current_state->regs->PC);
    printf("CPSR: %10d (0x%08x)\n", CPSR_convert(current_state),
           CPSR_convert(current_state));

}

void print_memory(State *current_state) {
    printf("Non-zero memory:\n");
    int k = 0;
    uint32_t PC = 0x0;
    for (k = 0; k < MEM_CAPACITY / BYTES_PER_WORD; k++) {
        if (current_state->mem[k] != 0x0) {
            printf("0x%.8x: 0x%.8x\n", PC, current_state->mem[k]);
        }
        PC += INCREMENT_PC;
    }
}

