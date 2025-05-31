/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_index
** File description:
** LLVM for index declaration
*/

#include "valka.h"
#include "valka_parser.h"

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
    data_types_t val_type = get_data_from_node(node->_ast_val._index._sym);
    data_types_t idx_type = get_data_from_node(node->_ast_val._index._index_val);
    data_types_t deref_type = get_deref_data_type(val_type);
    char *tmp = llvm_gen_value(node->_ast_val._index._sym, f, val_type);
    char *index_tmp = llvm_gen_value(node->_ast_val._index._index_val, f, idx_type);
    char *ptr_tmp = get_random_var_name();
    char *llvm_type = get_write_data_type(deref_type);

    fprintf(f, "%%%s = getelementptr inbounds %s, %s* %%%s, i32 %%%s\n",
        ptr_tmp, llvm_type, llvm_type, tmp, index_tmp);
    fprintf(f, "%%%s = load %s, %s* %%%s\n",
        dest, deref_type._llvm_ir, deref_type._llvm_ir, ptr_tmp);
    return OK_OUTPUT;
}
