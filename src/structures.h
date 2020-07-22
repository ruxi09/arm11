//
// Created by nicol on 25/05/2020.
//

#ifndef ARM11_10_STRUCTURES_H
#define ARM11_10_STRUCTURES_H
#define MEM_CAPACITY 65536
#define NO_OF_GENERAL_REGISTERS 13
#define INCREMENT_PC 0x4

#include <stdint.h>
//#define DEBUG

#ifdef DEBUG
#define LOG(format) printf(format)
#define LOG_ONE_ARG(format, arg) printf(format, arg)
#define LOG_TWO_ARG(format, arg1, arg2) printf(format, arg1, arg2)
#else
#define LOG(format)
#define LOG_ONE_ARG(format, arg)
#define LOG_TWO_ARG(format, arg1, arg2)
#endif

typedef enum {
    //Data processing
    DPR,
    //Multiply
    MUL,
    //Single Data Transfer
    SDT,
    //Branch
    BR,
    // None loaded or zero instruction
    NONE
} Instruction;

typedef struct CPSR {
    // Negative result
    int N;
    // Zero result
    int Z;
    // Result caused Carry-out
    int C;
    // Overflow
    int V;
} CPSR;

typedef enum {
    lsl = 0,
    lsr = 1,
    asr = 2,
    ror = 3
} Shift_type;

typedef uint32_t Memory;

typedef uint32_t Reg;

typedef struct {
    Reg PC;
    Reg general[NO_OF_GENERAL_REGISTERS];
    CPSR CPSR;
} Registers;

typedef enum {
    and = 0,
    eor = 1,
    sub = 2,
    rsb = 3,
    add = 4,
    tst = 8,
    teq = 9,
    cmp = 10,
    orr = 12,
    mov = 13
} Opcode;

typedef struct Instr_partition {
    Opcode opcode;
    int imm;
    int set;
    int acc;
    int pre;
    int up;
    int load;
    uint32_t rd;
    uint32_t rn;
    uint32_t rs;
    uint32_t rm;
    uint32_t offset;
    uint32_t operand2;
} Instr_partition;

typedef struct State {
    Instr_partition *decoded_part;
    Registers *regs;
    Memory *mem;
} State;

typedef struct Shift_Result {
    int carry_out;
    uint32_t data_out;
} Shift_result;

typedef enum {
    eq = 0,
    ne = 1,
    ge = 10,
    lt = 11,
    gt = 12,
    le = 13,
    al = 14
} Cond;

typedef enum {
    PIN_OFF = 0x20200028,
    PIN_ON = 0x2020001C,
    PIN_0_9 = 0x20200000,
    PIN_10_19 = 0x20200004,
    PIN_20_29 = 0x20200008,
} GPIO;

/*
 * any_t is a pointer.  This allows you to put arbitrary structures in
 * the hashmap.
 */
typedef void *any_t;

#define MAX_INSTR_COUNT 1000
#define LINE_MAX 511

typedef struct instr_state {
    uint32_t current_instr;
    uint32_t instr_count;
    uint32_t hex_format[MAX_INSTR_COUNT];
    char **full_instr;
    char **keywords;
} instr_state_t;

typedef void (*func_t)(instr_state_t *);

typedef any_t table_t;

#endif //ARM11_10_STRUCTURES_H
