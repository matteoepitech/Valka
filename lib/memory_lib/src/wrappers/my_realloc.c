/*
** EPITECH PROJECT, 2025
** src/wrappers/my_realloc.c
** File description:
** This file is for my_realloc wrapper
*/

#include "mymem.h"

/**
 * @brief Wrapper for REALLOC(ptr, size).
 *
 * @param pointer               The pointer to realloc
 * @param bytes                 The number of bytes to allocate
 *
 * @return The pointer reallocated.
 */
void *
my_realloc(IN void *pointer, IN size_t bytes)
{
    void *ptr_allocated = NULL;

    if (bytes == 0)
        return NULL;
    if (pointer == NULL)
        return my_malloc(bytes);
    ptr_allocated = malloc(bytes);
    ptr_allocated = my_memcpy(ptr_allocated, pointer, size_ptr(pointer));
    save_ptr(ptr_allocated, bytes);
    free_ptr(pointer);
    return ptr_allocated;
}
