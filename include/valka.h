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

    #include "../lib/memory_lib/include/mymem.h"

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

char *llvm_gen_value(ast_node_t *node, FILE *f, data_types_t type, bool_t load_val);
char *llvm_gen_address(ast_node_t *node, FILE *f, bool_t need_load);
void collect_all_strings(ast_program_t *prg, FILE *f);
uint8_t generate_load_literal(char *dest, data_types_t var_type, char *var_name, FILE *f);
void collect_strings(ast_node_t *node, FILE *f);

uint8_t dispatch_llvm(FILE *f, ast_statement_t *cur);

/*
 * Folder : core/llvm/dispatch
 */
uint8_t llvm_var(ast_node_t *node, FILE *f);
uint8_t llvm_func(ast_node_t *node, FILE *f);
uint8_t llvm_return(ast_node_t *node, FILE *f);
uint8_t llvm_call_sym(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_math(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_string(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_if(ast_node_t *node, FILE *f);
uint8_t llvm_condition(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_assign(ast_node_t *node, FILE *f);
uint8_t llvm_cast(ast_node_t *node, FILE *f, char *dest);
uint8_t llvm_for(ast_node_t *node, FILE *f);
uint8_t llvm_while(ast_node_t *node, FILE *f);
uint8_t llvm_index(UNUSED ast_node_t *node, FILE *f, char *dest, bool_t load_val);
uint8_t llvm_struct(ast_node_t *node, FILE *f);
uint8_t llvm_field(ast_node_t *node, FILE *f, char *dest, bool_t load_val);

/*
 * Folder : src/core/prepass/
 */
void prepass_buffer(parsing_src_file_t *p);

/*
 * Folder : utils/
 */
char *get_random_var_name(void);

/*
 * Folder : utils/strings/
 */
char *strndup_valka(const char *string, unsigned long size);
char *strdup_valka(const char *string);

/*
 * Folder : utils/definitions/
 */
uint8_t create_base_definitions(void);
uint8_t add_definition(char *def, char *val);

/*
 * Folder : src/utils/data/
 */
data_types_t get_data_type_from_token(token_t *token);
data_types_t get_data_with_id(uint32_t id);
data_types_t get_highest_data_type(data_types_t d1, data_types_t d2);
data_types_t get_data_from_node(ast_node_t *node);
data_types_t get_deref_data_type(data_types_t data);
char *get_write_data_type(data_types_t data, bool_t only_primitive);
data_types_t get_array_elem_data(data_types_t array_type);
bin_ope_t get_operator_with_char(char op);

#endif /* ifndef _VALKA_H_ */
