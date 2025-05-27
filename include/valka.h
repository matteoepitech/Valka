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
    #include <sys/syscall.h>

    #include "lib/memory_lib/include/mymem.h"

    #include "valka_parser.h"
    #include "misc/defines.h"
    #include "misc/macros.h"
    #include "misc/types.h"

    /* Getting the architecture of the processor which we compile valkaC */
    #if defined(__x86_64__) || defined(_M_X64)
        #define ARCH_X86_64
    #elif defined(__aarch64__) || defined(_M_ARM64)
        #define ARCH_ARM64
    #elif defined(__arm__) || defined(_M_ARM)
        #define ARCH_ARM32
    #elif defined(__i386__) || defined(_M_IX86)
        #define ARCH_X86_32
    #else
        #define ARCH_UNKNOWN
    #endif

/*
 * Folder : core/llvm/
 */
FILE *create_llvm(void);
uint8_t close_llvm(FILE *f);
void compile_llvm_to_executable(void);
void generate_llvm_global(FILE *f, ast_program_t *prg);

char *llvm_gen_value(ast_node_t *node, FILE *f, data_types_t type);
void collect_all_strings(ast_program_t *prg, FILE *f);
void collect_strings(ast_node_t *node, FILE *f);

/*
 * Folder : core/llvm/dispatch
 */
uint8_t llvm_var(ast_node_t *node, FILE *f);
uint8_t llvm_func(ast_node_t *node, FILE *f);
uint8_t llvm_return(ast_node_t *node, FILE *f);
uint8_t llvm_call_sym(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_math(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_syscall(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_string(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_if(ast_node_t *node, FILE *f);
uint8_t llvm_condition(ast_node_t *node, FILE *f, char *dest);
/*
 * Folder : utils/
 */
char *get_random_var_name(void);

#endif /* ifndef _VALKA_H_ */
