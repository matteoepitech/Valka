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
llvm_call_sym(ast_node_t *node, FILE *f, char *dest)
{
    const char *func_name = node->_ast_val._call_sym._sym_name;

    if (strcmp(func_name, SYSCALL_BUILTIN_NAME) == 0)
        return llvm_syscall(node, f, dest, node->_ast_val._call_sym._args[0]->_ast_val._int_literal._value);
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
