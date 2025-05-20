/*
** VALKA PROJECT, 2025
** include/misc/macros
** File description:
** Valka macros header file
*/


#ifndef _VALKA_MACROS_H_
    #define _VALKA_MACROS_H_

    #include <stdio.h>

    #include <stdio.h>

    #define PERROR(...) \
        fprintf(stderr, "[\x1b[31mERROR\x1b[0m] (%s:%d:%s) ", \
        __FILE__, __LINE__, __func__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n")

#endif /* ifndef _VALKA_MACROS_H_ */
