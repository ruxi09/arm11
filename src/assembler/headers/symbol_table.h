//
// Created by nicol on 11/06/2020.
//

#ifndef ARM11_10_SYMBOL_TABLE_H
#define ARM11_10_SYMBOL_TABLE_H

#include "../../structures.h"
#include "hashmap.h"

/* Generates a symbol table and initialises it */
/* Maps each keyword to the function which converts its instruction type to hex */
symbol_table_t *generate_symbol_table();

#endif //ARM11_10_SYMBOL_TABLE_H
