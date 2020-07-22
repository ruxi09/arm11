//
// Created by nicol on 27/05/2020.
//

#include <assert.h>
#include "../structures.h"
#include "headers/utils.h"
#include "headers/data_processing.h"
#include "headers/decoder.h"
#include "headers/single_data_transfer.h"
#include "headers/multiply.h"
#include "headers/branch.h"
#include <stdbool.h>
#include "headers/instructions_utils.h"

#define INSTR_CODE_MASK 0xc000000 // masks bits 28-27
#define INSTR_CODE_DPR_MUL 0x0      // if bits 28-27 are 00 then either DPR or MUL
#define INSTR_CODE_SDT 0x4000000   // if bits 28-27 are 01 then SDT
#define INSTR_CODE_BR 0x8000000    // if bits 28-27 are 10 then BR

#define MUL_CHECK_MASK 0xf0 // masks bits 7-4
#define MUL_CHECK 0x90      // if bits 7-4 are 1001 then MUL

/* Fetches instruction from memory */
Memory fetch(State *current_state) {
    assert(current_state->regs->PC % INCREMENT_PC == 0);
    uint32_t value = current_state->mem[current_state->regs->PC / INCREMENT_PC];
    LOG_ONE_ARG("fetched: 0x%.8x \n", value);
    return value;
}

/* Decodes instruction */
Instruction decode(uint32_t instr) {
    LOG_ONE_ARG("decoded instruction is: 0x%.8x \n", value);
    LOG_ONE_ARG("reversed instruction is: 0x%.8x \n", reverse(value));

    /* checks if the instruction is halt */
    if (instr == 0x0) {
        return NONE;
    }
    uint32_t instr_code = reverse(instr) & INSTR_CODE_MASK;
    uint32_t mul_mask;
    Instruction decoded = NONE;
    switch (instr_code) {
        case INSTR_CODE_SDT:
            LOG("Decoded instruction is SDT\n");
            decoded = SDT;
            break;
        case INSTR_CODE_BR:
            LOG("Decoded instruction is BR\n");
            decoded = BR;
            break;
        case INSTR_CODE_DPR_MUL:
            mul_mask = reverse(instr) & MUL_CHECK_MASK;
            // checks if multiply bits correspond to distinguish between multiply and dpr
            if (mul_mask == MUL_CHECK) {
                LOG("Decoded instruction is MUL\n");
                decoded = MUL;
            } else {
                LOG("Decoded instruction is DPR\n");
                decoded = DPR;
            }
            break;
    }
    return decoded;
}

/* Executes the instruction. Returns true if it executes a branch */
bool execute(State *current_state, Instruction instr) {
    LOG_ONE_ARG("executing instruction: 0x%.8x \n",
                current_state->mem[current_state->regs->PC - 8]);
    if (check_cond(current_state)) {
        switch (instr) {
            case DPR:
                LOG("Executing DPR \n");
                decode_data_process(current_state);
                LOG_ONE_ARG("\n Decoded opcode: 0x%.8x",
                            current_state->decoded_part->opcode);
                LOG_ONE_ARG("\n Decoded imm: 0x%.8x",
                            current_state->decoded_part->imm);
                LOG_ONE_ARG("\n Decoded set: 0x%.8x",
                            current_state->decoded_part->set);
                LOG_ONE_ARG("\n Decoded operand2: 0x%.8x",
                            current_state->decoded_part->operand2);
                LOG_ONE_ARG("\n Decoded rn: 0x%.8x",
                            current_state->decoded_part->rn);
                LOG_ONE_ARG("\n Decoded rd: 0x%.8x\n",
                            current_state->decoded_part->rd);
                data_processing(current_state);
                break;
            case MUL:
                LOG("Executing MUL \n");
                decode_multiply(current_state);
                LOG_ONE_ARG("\n Decoded rd: 0x%.8x",
                            current_state->decoded_part->rd);
                LOG_ONE_ARG("\n Decoded rn: 0x%.8x",
                            current_state->decoded_part->rn);
                LOG_ONE_ARG("\n Decoded rs: 0x%.8x",
                            current_state->decoded_part->rs);
                LOG_ONE_ARG("\n Decoded rm: 0x%.8x",
                            current_state->decoded_part->rm);
                LOG_ONE_ARG("\n Decoded acc: 0x%.8x",
                            current_state->decoded_part->acc);
                LOG_ONE_ARG("\n Decoded set: 0x%.8x\n",
                            current_state->decoded_part->set);
                multiply(current_state);
                break;
            case SDT:
                LOG("Executing SDT \n");
                decode_single_data_transfer(current_state);
                single_data_transfer(current_state);
                break;
            case BR:
                LOG("Executing BR \n");
                decode_branch(current_state);
                LOG_ONE_ARG("\n Decoded offset: 0x%.8x \n",
                            current_state->decoded_part->offset);
                branch(current_state);
                return true;
            default:
                break;
        }
    }
    return false;
}

// Introduce main function in order to test decode (using partial compilation):

/*
 * Defines some random values that can represent instructions as follows:
 *
#define bin_const_dpr 0x0110a0e3   // 0b0000_00_110101010101010100_0101_0100 dpr
#define bin_const_mul 0x3555494   // 0b0000_00_110101010101010100_1001_0100 mul
#define bin_const_sdt 0x7555494   // 0b0000_01_11010101010101010010010100 sdt
#define bin_const_br  0xB555494   // 0b0000_10_11010101010101010010010100 br

int main(void) {
    instruction decoded = decode(bin_const_dpr);
    switch (decoded) {
        case DPR:
            printf("Instruction is DATA PROCESSING \n");
            break;
        case MUL:
            printf("Instruction is MULTIPLY \n");
            break;
        case SDT:
            printf("Instruction is SINGLE DATA TRANSFER \n");
            break;
        case BR:
            printf("Instruction is BRANCH \n");
            break;
        default:
            perror("Could not execute instruction");
    }
    return 0;
}
*/
