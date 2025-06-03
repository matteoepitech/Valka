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
llvm_index(UNUSED ast_node_t *node, FILE *f, char *dest, bool_t load_val)
{
    data_types_t current_val_type = get_data_from_node(node->_ast_val._index._sym);
    char *address_tmp = llvm_gen_address(node, f, TRUE);

    current_val_type._ptr_level -= node->_ast_val._index._index_count;

    if (load_val == TRUE) {
        fprintf(f, "%%%s = load %s, %s* %%%s\n", dest,
            get_write_data_type(current_val_type, FALSE),
            get_write_data_type(current_val_type, FALSE), address_tmp);        
    } else {
        fprintf(f, "%%%s = bitcast %s* %%%s to %s*\n", dest,
            get_write_data_type(current_val_type, FALSE), address_tmp,
            get_write_data_type(current_val_type, FALSE));
    }
    return OK_OUTPUT;
}
