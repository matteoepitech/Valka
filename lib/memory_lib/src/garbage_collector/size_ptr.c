/*
** EPITECH PROJECT, 2025
** src/wrappers/my_ptrsize
** File description:
** Wrapper to get the size of the content of a pointer
*/

#include "mymem.h"

/**
 * @brief Get the size of the content of the pointer.
 *
 * @param pointer                       The pointer
 *
 * @return The size.
 */
size_t
size_ptr(IN void *pointer)
{
    garbage_collector_t *gc = NULL;
    mem_entry_t *tmp_node = NULL;
    size_t index = 0;

    if (pointer == NULL)
        return 0;
    gc = get_mem_garbage_collector();
    index = get_mem_hash_pointer(pointer, gc->_size_entries);
    for (tmp_node = gc->_entries[index]; tmp_node != NULL &&
        tmp_node->_pointer != pointer; tmp_node = tmp_node->_next);
    if (tmp_node == NULL)
        return 0;
    return tmp_node->_ptrsize;
}
