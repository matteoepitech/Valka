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
    data_types_t ret_type = node->_ast_val._return._return_data;
    ast_node_t *val = node->_ast_val._return._value;
    char *llvm_type = get_write_data_type(ret_type, FALSE);
    char *tmp = NULL;

    if (val == NULL)
        return KO_OUTPUT;
    tmp = llvm_gen_value(val, f, ret_type, TRUE);
    if (tmp == NULL)
        return KO_OUTPUT;
    fprintf(f, "ret %s %%%s\n", llvm_type, tmp);
    return OK_OUTPUT;
}
