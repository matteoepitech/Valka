/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_index
** File description:
** LLVM for index declaration
*/

#include "valka.h"

/**
 * @brief LLVM index declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 * @param dest           Where to go
 *
 * @return Everything worked?
 */
uint8_t
llvm_index(UNUSED ast_node_t *node, FILE *f, char *dest)
{
    data_types_t current_val_type = get_data_from_node(node->_ast_val._index._sym);
    char *address_tmp = llvm_gen_address(node, f, TRUE);

    current_val_type._ptr_level -= node->_ast_val._index._index_count;
    fprintf(f, "%%%s = load %s, %s* %%%s\n", dest,
        get_write_data_type(current_val_type),
        get_write_data_type(current_val_type), address_tmp);        
    return OK_OUTPUT;
}
