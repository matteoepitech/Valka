/*
** VALKA PROJECT, 2025
** include/valka
** File description:
** Valka header file
*/

#ifndef _VALKA_H_
    #define _VALKA_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <string.h>
    #include <unistd.h>
    #include <ctype.h>
    #include <errno.h>

    #include "lib/memory_lib/include/mymem.h"

    #include "valka_parser.h"
    #include "misc/defines.h"
    #include "misc/macros.h"
    #include "misc/types.h"

/*
 * Folder : core/llvm/
 */
FILE *create_llvm(void);
uint8_t close_llvm(FILE *f);
void compile_llvm_to_executable(void);
void generate_llvm_global(FILE *f, ast_program_t *prg);

/*
 * Folder : core/llvm/dispatch
 */
uint8_t llvm_var(ast_node_t *node, FILE *f);

#endif /* ifndef _VALKA_H_ */
