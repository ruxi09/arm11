//
// Created by crist on 5/28/2020.
//

#include "../structures.h"
#include "headers/instructions_utils.h"
#include <string.h>

void decode_data_process(State *current_state) {
    Instr_partition *decoded = current_state->decoded_part;
    memset(decoded, 0, sizeof(Instr_partition));
    uint32_t instr = get_instruction(current_state);
    decoded->opcode = (Opcode) get(instr, OPCODE_START, OPCODE_END);
    decoded->imm = get(instr, I_BIT, I_BIT + 1);
    decoded->set = get(instr, S_BIT, S_BIT + 1);
    decoded->operand2 = get(instr, OPERAND2_START, OPERAND2_END);
    decoded->rn = get(instr, RN_START, RN_END);
    decoded->rd = get(instr, RD_START, RD_END);
}

void decode_single_data_transfer(State *current_state) {
    Instr_partition *decoded = current_state->decoded_part;
    memset(decoded, 0, sizeof(Instr_partition));
    uint32_t instr = get_instruction(current_state);
    decoded->offset = get(instr, SDT_OFFSET_START, SDT_OFFSET_END);
    decoded->rd = get(instr, RD_START, RD_END);
    decoded->rn = get(instr, RN_START, RN_END);
    decoded->load = get(instr, L_BIT, L_BIT + 1);
    decoded->up = get(instr, U_BIT, U_BIT + 1);
    decoded->pre = get(instr, P_BIT, P_BIT + 1);
    decoded->imm = get(instr, I_BIT, I_BIT + 1);
}

void decode_multiply(State *current_state) {
    Instr_partition *decoded = current_state->decoded_part;
    memset(decoded, 0, sizeof(Instr_partition));
    uint32_t instr = get_instruction(current_state);
    // only in multiply rd and rn are inverted
    // a.k.a rd occupies the byte of rn and vice-versa
    decoded->rd = get(instr, RN_START, RN_END);
    decoded->rn = get(instr, RD_START, RD_END);
    decoded->rs = get(instr, RS_START, RS_END);
    decoded->rm = get(instr, RM_START, RM_END);
    decoded->acc = get(instr, A_BIT, A_BIT + 1);
    decoded->set = get(instr, S_BIT, S_BIT + 1);
}

void decode_branch(State *current_state) {
    Instr_partition *decoded = current_state->decoded_part;
    memset(decoded, 0, sizeof(Instr_partition));
    uint32_t instr = get_instruction(current_state);
    decoded->offset = get(instr, BR_OFFSET_START, BR_OFFSET_END);
}
