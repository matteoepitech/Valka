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
    data_types_t data = node->_ast_val._var_decl._var_type;
    char *llvm_type = get_write_data_type(data);
    char *tmp_val = NULL;

    fprintf(f, "%%%s = alloca %s\n", var_name, llvm_type);
    tmp_val = llvm_gen_value(value_node, f, data);
    fprintf(f, "store %s %%%s, %s* %%%s\n\n", llvm_type, tmp_val, llvm_type, var_name);
    return OK_OUTPUT;
}
