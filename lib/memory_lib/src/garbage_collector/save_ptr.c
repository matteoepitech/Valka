/*
** EPITECH PROJECT, 2025
** src/garbage_collector/save_ptr
** File description:
** This file contains functions for saving ptr in the garbage collector
*/

#include "mymem.h"

/**
 * @brief Wrapper for saving the pointer into the GC.
 *
 * @param pointer               The pointer to save
 *
 * @return Status of the function.
 */
mem_bool_t
save_ptr(IN void *pointer, IN size_t bytes)
{
    garbage_collector_t *gc = NULL;

    if (pointer == NULL)
        return _MEM_FALSE;
    gc = get_mem_garbage_collector();
    if (gc == NULL)
        return _MEM_FALSE;
    return add_mem_garbage_collector(pointer, bytes, gc);
}
