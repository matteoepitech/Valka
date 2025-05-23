/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_call_sym
** File description:
** LLVM for call symbol declaration
*/

#include "valka.h"

/**
 * @brief LLVM call symbol declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_call_sym(ast_node_t *node, FILE *f, const char *dest)
{
    const char *func_name = node->_ast_val._call_sym._sym_name;
    // @TODO get the type of the function and put it on the ast_val._call_sym

    if (dest == NULL) {
        fprintf(f, "call %s @%s(", "i32", func_name);
        // @TODO parameters
        fprintf(f, ")\n");
    } else {
        fprintf(f, "%%%s = call %s @%s(", dest, "i32", func_name);
        // @TODO parameters
        fprintf(f, ")\n");
    }
    return OK_OUTPUT;
}
