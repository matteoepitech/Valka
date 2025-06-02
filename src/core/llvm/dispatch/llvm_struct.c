/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_struct
** File description:
** LLVM for structure declaration
*/

#include "valka.h"

/**
 * @brief LLVM structure declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_struct(ast_node_t *node, FILE *f)
{
    const char *struct_name = node->_ast_val._struct._struct_name;
    uint32_t fields_count = node->_ast_val._struct._fields_count;
    ast_node_t **fields = node->_ast_val._struct._fields;

    fprintf(f, "%%%s = type {", struct_name);
    for (uint32_t i = 0; i < fields_count; i++) {
        if (i != 0) {
            fprintf(f, ", ");
        }
        fprintf(f, "%s",
            get_write_data_type(fields[i]->_ast_val._var_decl._var_type));
    }
    fprintf(f, "}\n\n");
    return OK_OUTPUT;
}
