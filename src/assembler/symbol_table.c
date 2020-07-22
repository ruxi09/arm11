//
// Created by Ruxi on 10/06/2020.
//
#include "headers/hashmap.h"
#include "headers/branch.h"
#include "headers/single_data_transfer_assembler.h"
#include "headers/data_processing.h"
#include "headers/multiply.h"

/* Handles halt instruction */
static void halt(instr_state_t *instr_state) {
    return;
}

/* Generates a symbol table and initialises it */
/* Maps each keyword to the function which converts its instruction type to hex */
symbol_table_t *generate_symbol_table() {
    symbol_table_t *symbol_table = symbol_table_new();

    symbol_table_put(symbol_table, "add", data_processing);
    symbol_table_put(symbol_table, "sub", data_processing);
    symbol_table_put(symbol_table, "rsb", data_processing);
    symbol_table_put(symbol_table, "and", data_processing);
    symbol_table_put(symbol_table, "eor", data_processing);
    symbol_table_put(symbol_table, "orr", data_processing);
    symbol_table_put(symbol_table, "mov", data_processing);
    symbol_table_put(symbol_table, "tst", data_processing);
    symbol_table_put(symbol_table, "teq", data_processing);
    symbol_table_put(symbol_table, "cmp", data_processing);
    symbol_table_put(symbol_table, "mul", multiply);
    symbol_table_put(symbol_table, "mla", multiply);
    symbol_table_put(symbol_table, "ldr", single_data_transfer);
    symbol_table_put(symbol_table, "str", single_data_transfer);
    symbol_table_put(symbol_table, "b", branch);
    symbol_table_put(symbol_table, "beq", branch);
    symbol_table_put(symbol_table, "bne", branch);
    symbol_table_put(symbol_table, "bge", branch);
    symbol_table_put(symbol_table, "bgt", branch);
    symbol_table_put(symbol_table, "ble", branch);
    symbol_table_put(symbol_table, "bge", branch);
    symbol_table_put(symbol_table, "lsl", data_processing);
    symbol_table_put(symbol_table, "andeq", halt);

    return symbol_table;
}
