//
// Created by Ruxi on 10/06/2020.
//

#ifndef ARM11_10_FILE_UTILS_H
#define ARM11_10_FILE_UTILS_H

#include <stdint.h>
#include "../../structures.h"

/* Loads file and adds full instructions to state */
void load_file(char *filename, instr_state_t *state);


/* Gets the keywords from each line of assembly */
/* By "keywords", we mean the first word from a line (mnemonic or label) */
void get_keywords(instr_state_t *state);

/* Binary file writer (writes from state->hex_format) */
void write_file(char *filename, instr_state_t *state);

#endif //ARM11_10_FILE_UTILS_H
