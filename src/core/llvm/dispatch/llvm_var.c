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
    const char *varname = node->_ast_val._var_decl._var_name;
    UNUSED const char *typeval = node->_ast_val._var_decl._type_value;
    ast_node_t *value_node = node->_ast_val._var_decl._value;

    if (value_node && value_node->_type == AST_LITERAL_INT) {
        fprintf(f, "@%s = global %s %d\n", varname, "i32", value_node->_ast_val._int_literal._value);
    }
    return OK_OUTPUT;
}
