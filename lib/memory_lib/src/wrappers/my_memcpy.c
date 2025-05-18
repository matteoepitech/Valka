/*
** EPITECH PROJECT, 2025
** src/wrappers/my_memcpy
** File description:
** Wrapper for my_memcpy
*/

#include "mymem.h"

/**
 * @brief Copy certain size of bytes into a dest pointer.
 *
 * @param dest                  Where to copy
 * @param src                   The src to copy
 * @param size                  The number of bytes to copy
 *
 * @return The pointer copied.
 */
void *
my_memcpy(void *dest, const void *src, size_t size)
{
    unsigned char *dest_char = NULL;
    const unsigned char *src_char = NULL;

    if (size == 0 || dest == NULL || src == NULL)
        return dest;
    dest_char = (unsigned char *) dest;
    src_char = (const unsigned char *) src;
    for (size_t i = 0; i < size; i++) {
        dest_char[i] = src_char[i];
    }
    return dest;
}
