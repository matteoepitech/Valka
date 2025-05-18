/*
** EPITECH PROJECT, 2025
** src/wrappers/my_malloc
** File description:
** This file is for my_malloc wrapper
*/

#include "mymem.h"

/**
 * @brief Wrapper for MALLOC(size).
 *
 * @param bytes                 The number of bytes to allocate
 *
 * @return The pointer allocated.
 */
void *
my_malloc(IN size_t bytes)
{
    void *ptr_allocated = NULL;
    unsigned char *tmp = NULL;

    if (bytes == 0)
        return NULL;
    ptr_allocated = malloc(bytes);
    if (ptr_allocated == NULL)
        exit(2);
    tmp = (unsigned char *)ptr_allocated;
    for (size_t i = 0; i < bytes; i++)
        tmp[i] = 0;
    save_ptr(ptr_allocated, bytes);
    return ptr_allocated;
}
