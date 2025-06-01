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
    ast_node_t *assigned_node = node->_ast_val._assignment._assigned;
    ast_node_t *value_node = node->_ast_val._assignment._value;
    data_types_t data = get_data_from_node(assigned_node);
    char *assigned_name = NULL;
    char *tmp_val = NULL;
    char *llvm_type = NULL;
    
    if (assigned_node->_type == AST_SYMBOL) {
        assigned_name = assigned_node->_ast_val._symbol._sym_name;
    } else if (assigned_node->_type == AST_INDEX) {
        assigned_name = llvm_gen_address(assigned_node, f, TRUE);
    } else {
        assigned_name = llvm_gen_value(assigned_node, f, data);
    }
    tmp_val = llvm_gen_value(value_node, f, data);
    llvm_type = get_write_data_type(data);
    fprintf(f, "store %s %%%s, %s* %%%s\n\n", llvm_type, tmp_val, llvm_type, assigned_name);
    return OK_OUTPUT;
}
