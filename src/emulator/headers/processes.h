//
// Created by nicol on 27/05/2020.
//


#ifndef ARM11_10_PROCESSES_H
#define ARM11_10_PROCESSES_H

#include <stdio.h>
#include <stdbool.h>

/* Fetches instruction from memory */
Memory fetch(State *current_state);

/* Decodes instruction */
Instruction decode(uint32_t value);

/* Executes the instruction. Returns true if it executes a branch */
bool execute(State *current_state, Instruction instr);

#endif //ARM11_10_PROCESSES_H
