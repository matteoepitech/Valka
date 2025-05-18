/*
** EPITECH PROJECT, 2025
** src/exit_cleanup
** File description:
** This file contains functions for cleaning all allocated ressources
** when exiting the program for example
*/

#include "mymem.h"

/**
 * @brief Free all the memory used at the exit of the program.
 *        Use __attribute__((destructor)) : If you want to clean auto.
 *        Valgrind doesn't support this and can not show good output.
 *
 * @param exit_code             The exit code
 *
 * @return The exit code.
 */
uint8_t cleanup_mem(uint8_t exit_code)
{
    garbage_collector_t *gc = get_mem_garbage_collector();
    mem_entry_t *tmp_node = NULL;
    mem_entry_t *next_node = NULL;

    if (gc == NULL)
        return exit_code;
    for (int i = 0; i < gc->_size_entries; i++) {
        tmp_node = gc->_entries[i];
        while (tmp_node != NULL) {
            next_node = tmp_node->_next;
            free_entry_node(tmp_node);
            tmp_node = next_node;
        }
    }
    free(gc->_entries);
    gc->_entries = NULL;
    free(gc);
    gc = NULL;
    return exit_code;
}
