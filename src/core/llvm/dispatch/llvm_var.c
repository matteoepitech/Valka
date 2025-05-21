/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_var
** File description:
** LLVM for variable declaration
*/

#include "valka.h"

/**
 * @brief LLVM var declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_var(ast_node_t *node, FILE *f)
{
    const char *var_name = node->_ast_val._var_decl._var_name;
    ast_node_t *value_node = node->_ast_val._var_decl._value;

    if (value_node && value_node->_type == AST_LITERAL_INT) {
        fprintf(f, "%%%s = alloca %s\n", var_name, "i32");
        fprintf(f, "store %s %d, %s* %%%s\n\n", "i32", value_node->_ast_val._int_literal._value, "i32", var_name);
    }
    return OK_OUTPUT;
}
