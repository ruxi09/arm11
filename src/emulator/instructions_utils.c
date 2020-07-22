#include <stdio.h>
#include <stdint.h>
#include "../structures.h"
#include "headers/instructions_utils.h"
#include "headers/utils.h"
#include "headers/processes.h"

#define MASKS_NO 8

/* Function to get bits between start and end: */
uint32_t get(uint32_t value, int start, int end) {
    uint32_t mask = (1 << (end - start)) - 1;
    return (value >> start) &
           mask;
}

/* Retrieves instruction pointed by PC: */
uint32_t get_instruction(State *current_state) {
    uint32_t PC_val = current_state->regs->PC - 2 * INCREMENT_PC;
    uint32_t instr = current_state->mem[PC_val / INCREMENT_PC];
    return reverse(instr);
}

/* Checks if COND is satisfied by CPSR */
int check_cond(State *current_state) {
    uint32_t instruction = get_instruction(current_state);
    switch (get(instruction, COND_START, COND_END)) {
        case eq :
            return current_state->regs->CPSR.Z;
        case ne :
            return !current_state->regs->CPSR.Z;
        case ge :
            return current_state->regs->CPSR.N == current_state->regs->CPSR.V;
        case lt :
            return current_state->regs->CPSR.N != current_state->regs->CPSR.V;
        case gt :
            return !current_state->regs->CPSR.Z &
                   (current_state->regs->CPSR.N == current_state->regs->CPSR.V);
        case le :
            return current_state->regs->CPSR.Z |
                   (current_state->regs->CPSR.N != current_state->regs->CPSR.V);
        case al :
            return 1;
        default:
            return 0;
    }
}

/* FUNCTIONS FOR SETTING THE C FLAG: */
/* For and, eor, orr, teq, tst, mov */
void set_C(State *current_state, int carry_out) {
    current_state->regs->CPSR.C = (uint8_t) carry_out;
}

/* For add */
void
set_C_add(State *current_state, uint32_t first_value, uint32_t second_value) {
    current_state->regs->CPSR.C = (first_value + second_value > MAX);
}

/* For sub, cmp, rsb */
void
set_C_sub(State *current_state, uint32_t first_value, uint32_t second_value) {
    current_state->regs->CPSR.C = (second_value >= first_value);
}

/* FUNCTION FOR SETTING BOTH N AND Z FLAGS: */
void set_N_Z(State *current_state, uint32_t result) {
    current_state->regs->CPSR.N = get(result, N_BIT, N_BIT + 1);
    current_state->regs->CPSR.Z = (!result);
}

/* Returns shift result of rotation */
Shift_result rotate(int shift_value, Reg rm) {
    Shift_result result;
    uint32_t temp;
    result.data_out = rm;
    while (shift_value > 0) {
        temp = (MASK_BIT_0 & result.data_out) << SHIFT_AMOUNT;
        result.data_out = temp | (result.data_out >> 1);
        shift_value--;
    }
    result.carry_out = (int) ((result.data_out & MASK_BIT_31) >> SHIFT_AMOUNT);
    return result;
}

/* To get immediate value: */
uint32_t immediate(int rotate_value, uint32_t imm) {
    uint32_t result;
    result = rotate(rotate_value << 1, imm).data_out;
    return result;
}

/* Executes shift */
Shift_result shift(State *current_state) {
    //init:
    int carry_bit = 0;
    uint32_t offset = 0;
    uint32_t instr = get_instruction(current_state);
    uint32_t shift = get(instr, SHIFT_START, SHIFT_END);
    uint32_t shifted_reg = get(instr, RM_START, RM_END);
    uint32_t shift_t = get(instr, SHIFT_T_START, SHIFT_T_END);

    Reg rm = current_state->regs->general[shifted_reg];

    if (!get(instr, OP_REG_BIT, OP_REG_BIT + 1)) {
        int sign_bit = get(instr, MSB, MSB + 1);
        uint32_t r_bits;
        uint32_t l_bits;
        switch (shift_t) {
            case lsl:
                offset = rm << shift;
                carry_bit = MAX_BITS - shift;
                break;
            case lsr:
                offset = rm >> shift;
                carry_bit = shift - 1;
                break;
            case asr:
                offset = rm >> shift;
                if (sign_bit) {
                    uint32_t mask = MAX << (MAX_BITS - shift);
                    offset |= mask;
                }
                carry_bit = shift - 1;
                break;
            case ror:
                r_bits = rm >> shift;
                l_bits = rm << (MAX_BITS - shift);
                offset = l_bits | r_bits;
                carry_bit = shift - 1;
                break;
            default:
                printf("Could not recognize shift type\n");
        }
        if (!shift) {
            carry_bit = 0;
        }
    } else {
        int reg_address = get(instr, OPT_SHIFT_AMOUNT_START,
                              OPT_SHIFT_AMOUNT_END);
        shift = current_state->regs->general[reg_address];
        offset = rm >> shift;
    }

    Shift_result result;
    result.data_out = offset;
    result.carry_out = carry_bit;
    return result;
}

/* Used to put the bytes in the right order for load */
uint32_t reverse_bytes(uint32_t value, int no_bytes) {
    uint32_t result = 0;
    for (int i = 0; i < no_bytes; i++) {
        result <<= 8;
        result = result | (value & 0xff);
        value >>= 8;
    }
    return result;
}

/* Loads instruction from memory */
uint32_t load(State *current_state, uint32_t address) {
    uint32_t result = 0;
    uint8_t byte_no = address % INCREMENT_PC;

    LOG_ONE_ARG("first: 0x%.8x \n", current_state->mem[address / INCREMENT_PC]);
    LOG_ONE_ARG("second 0x%.8x \n",
                current_state->mem[address / INCREMENT_PC + 1]);
    LOG_ONE_ARG("byte number: %d\n", byte_no);

    // initialises an array of masks which are complementary
    // the masks from positions 0-3 select the last corresponding number of bytes
    // the masks from positions 4-8 select the first corresponding number of bytes
    uint32_t masks[MASKS_NO] = {0xffffffff, 0xffffff, 0xffff, 0xff, 0xffffff00,
                                0xffff0000, 0xff000000, 0x0};

    LOG_ONE_ARG("first mask: 0x%.8x\n", masks[byte_no]);
    LOG_ONE_ARG("second mask: 0x%.8x \n", masks[MASKS_NO - 1 - byte_no]);

    // A memory group consists of 4 bytes
    // we use the masks above to get all selected bytes which can be at most on two consecutive groups
    uint32_t first_part =
            (current_state->mem[address / INCREMENT_PC]) & masks[byte_no];
    uint32_t second_part = (current_state->mem[address / INCREMENT_PC + 1]) &
                           masks[MASKS_NO - 1 - byte_no];

    LOG_ONE_ARG("first part: 0x%.8x \n", first_part);
    LOG_ONE_ARG("second part: 0x%.8x \n", second_part);

    /*
     * A memory group consists of 4 bytes.
     We add to the result the selected bytes from the first group on the last positions and the selected bytes from
     the second group to the first position as the memory is organised in little endian.
     To add the second part to the beginning we should first shift them to the end (in the right) then reverse
     the bytes and then shift them back in order for the shift to be performed correctly
     */
    result = reverse_bytes(first_part, BYTES_PER_WORD - byte_no) |
             (reverse_bytes(
                     second_part >> BITS_PER_BYTE * (BYTES_PER_WORD - byte_no),
                     byte_no)
                     << BITS_PER_BYTE * (BYTES_PER_WORD - byte_no));

    LOG_ONE_ARG("Result: 0x%.8x\n", result);
    return result;
}

/* Stores instruction to memory */
void store(State *current_state, uint32_t address, uint32_t value) {

    uint8_t byte_no = address % INCREMENT_PC;
    if (byte_no == 0) {
        // if the byte number is zero we can simply take the whole group from memory as all four bytes are there
        current_state->mem[address / INCREMENT_PC] = reverse(value);
    } else {
        LOG_ONE_ARG("%d \n", byte_no);

        /* initialises an array of masks which are complementary */
        uint32_t masks[MASKS_NO] = {0x0, 0xffffff, 0xffff, 0xff, 0xffffff00,
                                    0xffff0000, 0xff000000, 0xffffffff};

        /* we use the mask to split the value in two parts, each is going to go in a different memory group */
        value = reverse(value);
        uint32_t first_part = value & masks[byte_no];
        uint32_t second_part = (value & masks[MASKS_NO - 1 - byte_no])
                >> (BITS_PER_BYTE * byte_no);

        LOG_ONE_ARG("first part: 0x%.8x \n", first_part);
        LOG_ONE_ARG("second part: 0x%.8x \n", second_part);

        /*
         * A memory group consists of 4 bytes.
         The masks from positions 0-3 set the corresponding first number of bytes to 0 to make space for the stored value
         in the first memory group computed from the address.
         The masks from positions 4-8 set the corresponding last number of bytes to 0 to make space for the stored value
         in the following memory group computed from the address.
        */

        current_state->mem[address / INCREMENT_PC] =
                (current_state->mem[address / INCREMENT_PC]) &
                masks[MASKS_NO - 1 - byte_no];
        current_state->mem[address / INCREMENT_PC + 1] =
                (current_state->mem[address / INCREMENT_PC + 1]) &
                masks[byte_no];

        LOG_ONE_ARG("first mask: 0x%.8x \n",
                    current_state->mem[address / INCREMENT_PC]);
        LOG_ONE_ARG("second mask: 0x%.8x \n",
                    current_state->mem[address / INCREMENT_PC + 1]);
        LOG("\n");

        /* We now store the value in memory */
        current_state->mem[address / INCREMENT_PC] =
                current_state->mem[address / INCREMENT_PC] | second_part;
        current_state->mem[address / INCREMENT_PC + 1] =
                current_state->mem[address / INCREMENT_PC + 1] | first_part;
    }

}

/* Performs GIPO checks */
int is_GPIO(uint32_t address) {
    switch (address) {
        case PIN_OFF:
            printf("PIN OFF\n");
            return 1;
        case PIN_ON:
            printf("PIN ON\n");
            return 1;
        case PIN_0_9:
            printf("One GPIO pin from 0 to 9 has been accessed\n");
            return 1;
        case PIN_10_19:
            printf("One GPIO pin from 10 to 19 has been accessed\n");
            return 1;
        case PIN_20_29:
            printf("One GPIO pin from 20 to 29 has been accessed\n");
            return 1;
        default:
            return 0;
    }
}
