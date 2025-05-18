/*
** EPITECH PROJECT, 2025
** mymem.h
** File description:
** Header for mymem
*/

#ifndef MY_MEM_H_
    #define MY_MEM_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <stdio.h>

    /*
     * Memory defines constants
     */
    #define _MEM_TRUE 1
    #define _MEM_FALSE 0

    #define _MEM_SMALL_GC 20
    #define _MEM_MEDIUM_GC 1543
    #define _MEM_BIG_GC 3079

    /*
     * Define for debugging and development, used for the mem lib only
     */
    #define WRITE_MEM(fd, msg) write(fd, msg, sizeof msg)

    /*
     * Define for wrapper basic allocation memory functions
     */
    #define MALLOC(size) my_malloc(size)
    #define REALLOC(ptr, size) my_realloc(ptr, size)

    #define PRINT_GC() print_mem_garbage_collector(get_mem_garbage_collector())

    /*
     * Indicator parameter functions
     */
    #ifndef IN
        #define IN
    #endif /* ifndef IN */

    #ifndef OUT
        #define OUT
    #endif /* ifndef OUT */


/*
 * Memory typedef
 */
typedef uint8_t mem_bool_t;


/*
 * Memory structures
 */
typedef struct mem_entry_s {
    void *_pointer;
    size_t _ptrsize;
    struct mem_entry_s *_next;
} mem_entry_t;

typedef struct {
    mem_entry_t **_entries;
    uint16_t _size_entries;
    uint32_t _total_bytes;
} garbage_collector_t;

/*
 * Wrapper memory functions
 */
void *my_malloc(size_t bytes);
void *my_realloc(void *pointer, size_t bytes);
void *my_memcpy(void *dest, const void *src, size_t size);

/*
 * Garbage collector functions
 */
garbage_collector_t *get_mem_garbage_collector(void);

mem_bool_t add_mem_garbage_collector(void *pointer, size_t bytes,
    garbage_collector_t *gc);
mem_bool_t remove_mem_garbage_collector(void *pointer,
    garbage_collector_t *gc);

mem_bool_t print_mem_garbage_collector(garbage_collector_t *gc);
uint16_t get_mem_hash_pointer(void *pointer, size_t size_gc);

mem_bool_t free_entry_node(IN mem_entry_t *entry);


mem_bool_t free_ptr(IN void *pointer);
mem_bool_t save_ptr(IN void *pointer, IN size_t bytes);
size_t size_ptr(void *pointer);

uint8_t cleanup_mem(uint8_t exit_code);

#endif /* ifndef MY_MEM_H_ */
