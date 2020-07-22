//
// Created by crist on 5/29/2020.
//

#include <assert.h>
#include <stdio.h>
#include "headers/single_data_transfer.h"
#include "../structures.h"
#include "headers/instructions_utils.h"

/* Executes an instruction whose type is SINGLE DATA TRANSFER */

void single_data_transfer(State *current_state) {
    Instr_partition *decoded = current_state->decoded_part;

    assert(decoded->rm != PC_ADDRESS && decoded->rd != PC_ADDRESS);
    assert(decoded->pre || decoded->rm != decoded->rn);

    uint32_t address = current_state->regs->general[decoded->rn];
    int32_t offs;
    if (decoded->imm) {
        offs = shift(current_state).data_out;
    } else {
        offs = decoded->offset;
    }

    if (!decoded->up) {
        offs = -offs;
    }

    LOG_TWO_ARG("Rn register %d at address: 0x%.8x\n", decoded->rn, address);
    if (PC_ADDRESS == decoded->rn) {
        offs += current_state->regs->PC;
    }

    if (decoded->pre) {
        address += offs;
    }

    LOG_ONE_ARG("offset: 0x%.8x \n", offs);
    LOG_ONE_ARG("Address: 0x%.8x\n", address);
    if (!is_GPIO(address)) {
        if (address > MEM_CAPACITY) {
            printf("Error: Out of bounds memory access at address 0x%08x\n",
                   address);
            return;
        }

        if (decoded->load) {        //load instruction
            LOG_TWO_ARG("Loading in register %d address 0x%.8x \n ",
                        decoded->rd, load(current_state, address));
            current_state->regs->general[decoded->rd] = load(current_state,
                                                             address);

        } else {                    //store instruction
            store(current_state, address,
                  current_state->regs->general[decoded->rd]);
        }

    } else if (decoded->load) {
        current_state->regs->general[decoded->rd] = address;
    }

    if (!decoded->pre) {
        current_state->regs->general[decoded->rn] += offs;
    }
}


