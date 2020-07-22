#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "emulator/headers/utils.h"
#include "emulator/headers/processes.h"
#include <stdbool.h>

// used for debugging in pipeline
void print(Instruction instr) {
    switch (instr) {
        case NONE:
            LOG("Instruction is NONE \n");
            break;
        case DPR:
            LOG("Instruction is DATA PROCESSING \n");
            break;
        case MUL:
            LOG("Instruction is MULTIPLY \n");
            break;
        case SDT:
            LOG("Instruction is SINGLE DATA TRANSFER \n");
            break;
        case BR:
            LOG("Instruction is BRANCH \n");
            break;
        default:
            LOG("Could not recognise instruction \n");
            break;
    }
}

/*
 *  Simulates the execution of the pipeline:
 *
 *       STAGE 0            STAGE 1    ........................................................... STAGE n
 *      INITIALISE    ENTER WHILE LOOP ........................................................... EXIT WHILE LOOP
 *          |               |
 *          |               |       +--------------+--------------+--------------+--------------+
 *          |               v       |  execute i1  |  execute i2  |  execute i3  |  execute i4  | ......
 *          |        +--------------+--------------+--------------+--------------+--------------+
 *          v        |   decode i1  |   decode i2  |   decode i3  |   decode i4  | .....................
 *    +--------------+--------------+--------------+--------------+--------------+
 *    |   fetch i1   |   fetch i2   |   fetch i3   |   fetch i4   | ....................................
 *    +--------------+--------------+--------------+--------------+
 *
 *    PC should be incremented at each stage
 */

void pipeline(State *current_state) {
    Memory fetched = fetch(current_state);
    current_state->regs->PC += INCREMENT_PC;
    Instruction decoded = NONE;
    Instruction to_execute = NONE;
    //used for printing when debugging
    int cnt = 1;
    bool is_branch = false;
    while (!(fetched == 0 && decoded == NONE && to_execute == NONE)) {
        LOG_ONE_ARG("stage %d: \n", cnt);
        LOG_ONE_ARG("fetched instr is: %.8x \n", fetched);
        LOG("\n");
        LOG("decoded instr is: \n");
        print(decoded);
        LOG("\n");
        LOG("executed instr is: \n");
        print(to_execute);
        LOG("\n");

        if (decoded != NONE) {
            to_execute = decoded;
            decoded = NONE;
            is_branch = execute(current_state, to_execute);
            to_execute = NONE;
        }

        if (is_branch) {
            to_execute = NONE;
            LOG_ONE_ARG("Fetching instr at address 0x%.8x \n",
                        current_state->regs->PC);
            fetched = fetch(current_state);
            is_branch = false;
        } else {
            decoded = decode(fetched);
            if (decoded == NONE) {
                // used for getting out of the while loop. Otherwise, decoded is seen as andeq r0, r0, r0 so seen as DPR
                // We must make sure that if this happens the while loop is exited immediately, hence fetched = 0x0.
                fetched = 0x0;
            } else {
                fetched = fetch(current_state);
            }
        }
        current_state->regs->PC += INCREMENT_PC;
        // used for printing when debugging
        cnt++;
    }
}

int main(int argc, char **argv) {

    State *current_state = malloc(sizeof(State));

    current_state->mem = calloc(MEM_CAPACITY, 1);
    current_state->regs = malloc(
            (NO_OF_GENERAL_REGISTERS + 2) * sizeof(Registers));
    current_state->decoded_part = malloc(sizeof(Instr_partition));

    FILE *input = NULL;
    input = get_file(input, argc, argv[1], current_state);
    read(input, current_state);

    initialise_registers(current_state);

    pipeline(current_state);

    print_registers(current_state);
    print_memory(current_state);

    free_state(current_state);
    fclose(input);
    exit(EXIT_SUCCESS);
}
