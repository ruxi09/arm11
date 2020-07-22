//
// Created by nicol on 29/05/2020.
//
#include "../structures.h"
#include "headers/instructions_utils.h"

#define OFFSET_SHIFT_AMOUNT 23
#define MASK_LAST_6_BYTES 0xffffff
#define MASK_BIT_24 0x800000
#define MASK_FIRST_2_BYTES 0xff000000

uint32_t sign_extension(uint32_t instr) {
    uint32_t value = (MASK_LAST_6_BYTES & instr);
    uint32_t sign = (MASK_BIT_24 & instr) >> OFFSET_SHIFT_AMOUNT;
    if (sign == 1) {
        value += MASK_FIRST_2_BYTES;
    }
    return value;
}

/* Executes an instruction whose type is BRANCH */
void branch(State *current_state) {
    Instr_partition *instr = current_state->decoded_part;
    uint32_t offset = instr->offset;
    offset = sign_extension((offset << 2));
    current_state->regs->PC += offset;
    LOG_ONE_ARG("Branching to address: 0x%.8x\n", current_state->regs->PC);
}
