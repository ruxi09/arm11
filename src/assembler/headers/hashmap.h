//
// Created by nicol on 11/06/2020.
//

#ifndef ARM11_10_HASHMAP_H
#define ARM11_10_HASHMAP_H

#define MAP_FULL -2    /* Hashmap is full */
#define MAP_OMEM -1    /* Out of Memory */
#define MAP_OK 0    /* OK */

#include <stdint.h>
#include "../../structures.h"

typedef struct symbol_table_elem {
    const char *key;
    int in_use;
    func_t data;
} symbol_table_elem_t;

typedef struct symbol_table {
    int table_size;
    int size;
    struct symbol_table_elem *data;
} symbol_table_t;

/*
 * Return an empty hashmap. Returns NULL if empty.
*/
extern symbol_table_t *symbol_table_new();

/*
 * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
 */
extern int symbol_table_put(symbol_table_t *table, const char *key, func_t value);

/*
 * Get an element from the hashmap. Return NULL if the element is not present.
 */
extern func_t symbol_table_get(symbol_table_t *table, const char *key);


/*
 * Free the hashmap
 */
extern void symbol_table_free(symbol_table_t *table);


#endif //ARM11_10_HASHMAP_H
