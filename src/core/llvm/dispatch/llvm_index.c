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

// @KEEP_HERE: old code to make the index get value.
// Here in case this ^ is not working very well.
/*
 *
uint8_t
llvm_index(UNUSED ast_node_t *node, FILE *f, char *dest)
{
    data_types_t current_val_type = get_data_from_node(node->_ast_val._index._sym);
    char *current_tmp = llvm_gen_value(node->_ast_val._index._sym, f, current_val_type);
    for (size_t i = 0; i < node->_ast_val._index._index_count; i++) {
        data_types_t idx_type = get_data_from_node(node->_ast_val._index._indices[i]);
        data_types_t deref_type = get_deref_data_type(current_val_type);
        char *index_tmp = llvm_gen_value(node->_ast_val._index._indices[i], f, idx_type);
        char *ptr_tmp = get_random_var_name();
        char *llvm_type = get_write_data_type(deref_type);

        fprintf(f, "%%%s = getelementptr inbounds %s, %s* %%%s, i32 %%%s\n",
            ptr_tmp, llvm_type, llvm_type, current_tmp, index_tmp);
        current_tmp = ptr_tmp;
        current_val_type = deref_type;
    }
    current_tmp = llvm_gen_address(node, f);
    fprintf(f, "%%%s = load %s, %s* %%%s\n", dest,
        get_write_data_type(current_val_type),
        get_write_data_type(current_val_type), current_tmp);
    return OK_OUTPUT;
}
 */
