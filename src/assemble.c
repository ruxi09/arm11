#include <stdlib.h>
#include <stdio.h>
#include "assembler/headers/file_utils.h"
#include "assembler/headers/symbol_table.h"

#define ARGUMENT_COUNT 3

int main(int argc, char **argv) {
    /* Check the argument count is correct */
    if (argc != ARGUMENT_COUNT) {
        printf("wrong number of arguments");
        exit(EXIT_FAILURE);
    }

    /* Alloc space for state */
    instr_state_t *state = calloc(1, sizeof(instr_state_t));
    if (!state) {
        perror("Allocation failed");
        exit (EXIT_FAILURE);
    }

    /* Load instructions into buffer line by line */
    load_file(argv[1], state);

    /* Generate the symbol table
    * This keeps track of each instruction keyword and its associated function pointer
    */
    symbol_table_t *table = generate_symbol_table();

    /* Initialises hex_format with zeros */
    for (int i = 0; i < 2 * state->instr_count; i++) {
        state->hex_format[i] = 0;
    }

    get_keywords(state);

    state->current_instr = 0;
    int initial_instr_count = state->instr_count;

    while (state->current_instr < initial_instr_count) {

        func_t func = symbol_table_get(table,
                                       state->keywords[state->current_instr]);

        if (func) {
            func(state);
        }

        state->current_instr++;
    }

    write_file(argv[2], state);

    symbol_table_free(table);
    for (int i = 0; i < initial_instr_count; i++) {
        free(state->full_instr[i]);
        free(state->keywords[i]);
    }
    free(state->full_instr);
    free(state->keywords);
    free(state);

    exit(EXIT_SUCCESS);
}
