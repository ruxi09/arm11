//
// Created by nicol on 29/05/2020.
//
#include "../structures.h"
#include "headers/instructions_utils.h"
#include <stdio.h>

/* Executes an instruction whose type is MULTIPLY */
void multiply(State *current_state) {

    Instr_partition *instr = current_state->decoded_part;
    Reg *access_registers = current_state->regs->general;

    Reg rm = access_registers[instr->rm];
    Reg rs = access_registers[instr->rs];
    Reg rn = access_registers[instr->rn];

    access_registers[instr->rd] = rm * rs;

    if (instr->acc) {
        access_registers[instr->rd] += rn;
    }

    if (instr->set) {
        set_N_Z(current_state, access_registers[instr->rd]);
    }

}
