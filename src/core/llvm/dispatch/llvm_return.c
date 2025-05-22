/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_return
** File description:
** LLVM for return declaration
*/

#include "valka.h"

/**
 * @brief LLVM return declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_return(ast_node_t *node, FILE *f)
{
    const char *ret_var = node->_ast_val._return._sym_name;
    const char *ret_var_tmp = "__ret_val__";

    if (node->_ast_val._return._return_id == RETURN_ID_SYMBOL) {
        fprintf(f, "%%%s = load %s, %s* %%%s\n", ret_var_tmp, "i32", "i32", ret_var);
        fprintf(f, "ret %s %%%s\n", "i32", ret_var_tmp);
    }
    if (node->_ast_val._return._return_id == RETURN_ID_INT) {
        fprintf(f, "ret %s %d\n", "i32", node->_ast_val._return._value->_ast_val._int_literal._value);
    }
    return OK_OUTPUT;
}
