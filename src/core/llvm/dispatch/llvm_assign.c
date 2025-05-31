/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_assign
** File description:
** LLVM for assignment declaration
*/

#include "valka.h"

/**
 * @brief LLVM assignment declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_assign(ast_node_t *node, FILE *f)
{
    char *var_name = node->_ast_val._assignment._var_name;
    ast_node_t *value_node = node->_ast_val._assignment._value;
    data_types_t data = get_sym_decl_from_name(node->_parent, var_name)->_ast_val._var_decl._var_type;
    char *tmp_val = llvm_gen_value(value_node, f, data);
    char *llvm_type = get_write_data_type(data);

    fprintf(f, "store %s %%%s, %s* %%%s\n\n", llvm_type, tmp_val, llvm_type, var_name);
    return OK_OUTPUT;
}
