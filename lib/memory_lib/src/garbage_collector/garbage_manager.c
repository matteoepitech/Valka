/*
** EPITECH PROJECT, 2025
** src/garbage_collector/garbage_manager
** File description:
** This file contains functions for managing the garbage collector
*/

#include "mymem.h"

/**
 * @brief Create the garbage collector array using a sizes of indexes.
 *
 * @param sizes                 The number of indexes availables in the array
 *
 * @return The memory entries. Used in the garbage_collector_t.
 */
static mem_entry_t **
create_mem_entries(IN uint16_t sizes)
{
    mem_entry_t **entries = malloc(sizeof(mem_entry_t *) * (sizes));

    if (entries == NULL)
        return NULL;
    for (int i = 0; i < sizes; i++) {
        entries[i] = malloc(sizeof(mem_entry_t));
        if (entries[i] == NULL)
            return NULL;
        entries[i]->_pointer = NULL;
        entries[i]->_next = NULL;
    }
    return entries;
}

/**
* @brief Create a mem entry node using a pointer.
*
* @param pointer                The pointer to create the node
*
* @return The mem_entry_t.
*/
static mem_entry_t *
create_mem_entry_node(IN void *pointer, IN size_t bytes)
{
    mem_entry_t *node = malloc(sizeof(mem_entry_t));

    if (node == NULL)
        return NULL;
    node->_pointer = pointer;
    node->_ptrsize = bytes;
    node->_next = NULL;
    return node;
}

/**
 * @brief Free an entry node.
 *
 * @param entry                 The entry to free
 *
 * @return Status of the function.
 */
mem_bool_t
free_entry_node(IN mem_entry_t *entry)
{
    if (entry == NULL)
        return _MEM_FALSE;
    if (entry->_pointer != NULL)
        free(entry->_pointer);
    entry->_pointer = NULL;
    free(entry);
    return _MEM_TRUE;
}

/**
 * @brief Print the garbage collector pointers.
 *
 * @param gc                     The garbage_collector_t to print
 *
 * @return Status of the function.
 */
mem_bool_t
print_mem_garbage_collector(IN garbage_collector_t *gc)
{
    mem_entry_t *node = NULL;

    if (gc == NULL)
        return _MEM_FALSE;
    for (int i = 0; i < gc->_size_entries; i++) {
        node = gc->_entries[i];
        while (node != NULL && node->_pointer != NULL) {
            printf("Pointer [%i] : %p\n", i, node->_pointer);
            node = node->_next;
        }
    }
    printf("\033[33mTotal bytes availables for freeing : %u\033[0m\n",
        gc->_total_bytes);
    return _MEM_TRUE;
}

/**
 * @brief Add a pointer in the GC, using a hash table.
 *
 * @param pointer                The pointer to store
 * @param gc                     The GC to store the pointer
 *
 * @return Status of the function.
 */
mem_bool_t
add_mem_garbage_collector(IN void *pointer, IN size_t bytes,
    IN garbage_collector_t *gc)
{
    size_t index = 0;
    mem_entry_t *head = NULL;
    mem_entry_t *new_node = NULL;

    if (pointer == NULL || gc == NULL)
        return _MEM_FALSE;
    index = get_mem_hash_pointer(pointer, gc->_size_entries);
    new_node = create_mem_entry_node(pointer, bytes);
    if (new_node == NULL)
        return _MEM_FALSE;
    head = gc->_entries[index];
    gc->_entries[index] = new_node;
    gc->_entries[index]->_next = head;
    gc->_total_bytes += bytes;
    return _MEM_TRUE;
}

/**
* @brief Remove the given pointer from the GC.
*
* @param pointer                The pointer to remove
* @param gc                     The GC to remove the pointer
*
* @return Status of the function;
*/
mem_bool_t
remove_mem_garbage_collector(IN void *pointer, IN garbage_collector_t *gc)
{
    size_t index = 0;
    mem_entry_t *tmp_node = NULL;
    mem_entry_t *next_node = NULL;
    mem_entry_t *prev_node = NULL;

    if (pointer == NULL || gc == NULL)
        return _MEM_FALSE;
    index = get_mem_hash_pointer(pointer, gc->_size_entries);
    for (tmp_node = gc->_entries[index]; tmp_node != NULL &&
        tmp_node->_pointer != pointer; tmp_node = tmp_node->_next)
        prev_node = tmp_node;
    if (tmp_node == NULL)
        return _MEM_FALSE;
    next_node = tmp_node->_next;
    free_entry_node(tmp_node);
    if (prev_node == NULL)
        gc->_entries[index] = next_node;
    else
        prev_node->_next = next_node;
    return _MEM_TRUE;
}

/**
 * @brief Get the garbage collector structure.
 *
 * @return The garbage collector of the program.
 */
garbage_collector_t *
get_mem_garbage_collector(void)
{
    static garbage_collector_t *gc = NULL;

    if (gc == NULL) {
        gc = malloc(sizeof(garbage_collector_t));
        gc->_size_entries = _MEM_SMALL_GC;
        gc->_entries = create_mem_entries(gc->_size_entries);
        gc->_total_bytes = 0;
    }
    return gc;
}
