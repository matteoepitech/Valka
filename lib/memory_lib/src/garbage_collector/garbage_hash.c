/*
** EPITECH PROJECT, 2025
** src/garbage_collector/garbage_hash
** File description:
** This file contains functions for helping of indexing the poitner
*/

#include "mymem.h"

/**
* @brief Hash the pointer into an index, to get the value in the hash table.
*
* @param pointer                The pointer to hash
* @param size_gc                The size of the hash table (GC)
*
* @return The index of the pointer.
*/
uint16_t get_mem_hash_pointer(IN void *pointer, IN size_t size_gc)
{
    return (uint16_t) (((size_t) pointer >> 3) % size_gc);
}
