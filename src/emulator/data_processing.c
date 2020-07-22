#include "../structures.h"
#include "headers/instructions_utils.h"
#include "headers/operations.h"

/* Executes an instruction whose type is DATA PROCESSING */

void data_processing(State *current_state) {
    // init:
    Instr_partition *instr = current_state->decoded_part;
    Reg rn = current_state->regs->general[instr->rn];
    int carry_out = 0;
    uint32_t result = 0;
    uint32_t operand2;

/*  Calculates the correct operand2 value based on whether the instruction is
 * immediate */

    if (instr->imm) {
        uint32_t imm = (instr->operand2) & MASK_IMMEDIATE;
        int rotate_value = (int) (((instr->operand2) & MASK_ROTATE)
                >> SHIFT_ROTATE);
        operand2 = immediate(rotate_value, imm);
    } else {
        Shift_result op2 = shift(current_state);
        operand2 = op2.data_out;
        carry_out = op2.carry_out;
    }

/*  Performs operations to the registers based on the opcode */

    switch (instr->opcode) {
        case and :
            LOG("Executing and \n");
            current_state->regs->general[instr->rd] = do_and(rn, operand2);
            break;
        case eor :
            LOG("Executing eor \n");
            current_state->regs->general[instr->rd] = do_eor(rn, operand2);
            break;
        case sub :
            LOG("Executing sub \n");
            current_state->regs->general[instr->rd] = do_sub(rn, operand2);
            break;
        case rsb :
            LOG("Executing rsb \n");
            current_state->regs->general[instr->rd] = do_rsb(rn, operand2);
            break;
        case add :
            LOG("Executing add \n");
            current_state->regs->general[instr->rd] = do_add(rn, operand2);
            break;
        case tst :
            LOG("Executing tst \n");
            result = do_tst(rn, operand2);
            break;
        case teq :
            LOG("Executing teq \n");
            result = do_teq(rn, operand2);
            break;
        case cmp :
            LOG("Executing cmp \n");
            result = do_cmp(rn, operand2);
            break;
        case orr :
            LOG("Executing orr \n");
            current_state->regs->general[instr->rd] = do_orr(rn, operand2);
            break;
        case mov :
            LOG("Executing mov\n");
            current_state->regs->general[instr->rd] = operand2;
            break;
        default:
            LOG("Could not recognize instruction \n");
            break;
    }

/*  If the flags are supposed to be set, the appropriate helper functions are
 *  called to set the appropriate flags */
    if (instr->set) {
        switch (instr->opcode) {
            case and :
            case eor :
            case orr :
            case teq :
            case tst :
            case mov :
                set_C(current_state, carry_out);
                break;
            case sub :
            case cmp :
                set_C_sub(current_state, operand2, rn);
                break;
            case rsb :
                set_C_sub(current_state, rn, operand2);
                break;
            case add :
                set_C_add(current_state, rn, operand2);
                break;
        }
        set_N_Z(current_state, result);
    }
}

