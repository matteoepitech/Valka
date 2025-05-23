/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_func
** File description:
** LLVM for function declaration
*/

#include "valka.h"

/**
 * @brief LLVM func declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_func(ast_node_t *node, FILE *f)
{
    const char *func_name = node->_ast_val._function._func_name;
    data_types_t func_ret = node->_ast_val._function._return_data;
    ast_program_t *func_content = node->_ast_val._function._func_content;

    fprintf(f, "define %s @%s()\n", func_ret._llvm_ir, func_name);
    fprintf(f, "{\n");
    fprintf(f, "entry:\n\n");
    generate_llvm_global(f, func_content);
    fprintf(f, "}\n\n");
    return OK_OUTPUT;
}
