/*
** EPITECH PROJECT, 2025
** src/garbage_collector/free_ptr.c
** File description:
** This file contains functions for freeing ptr in the garbage collector
*/

#include "mymem.h"

/**
 * @brief Wrapper for freeing the pointer from the GC.
 *
 * @param pointer               The pointer to free
 *
 * @return Status of the function.
 */
mem_bool_t
free_ptr(IN void *pointer)
{
    garbage_collector_t *gc = NULL;

    if (pointer == NULL)
        return _MEM_FALSE;
    gc = get_mem_garbage_collector();
    if (gc == NULL)
        return _MEM_FALSE;
    return remove_mem_garbage_collector(pointer, gc);
}
