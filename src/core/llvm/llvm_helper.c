/*
** VALKA PROJECT, 2025
** src/core/llvm/llvm_helper
** File description:
** LLVM helper
*/

#include "valka.h"

/**
 * @brief Generate the parameter loading from a function.
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 *
 * @return If we found the symbol or not.
 */
static uint8_t
generate_symbol_from_param(ast_node_t *node, FILE *f, char *tmp)
{
    uint32_t func_params_count = node->_parent->_parent->_ast_val._function._params_count;
    ast_node_t **func_params = node->_parent->_parent->_ast_val._function._params;

    for (uint32_t i = 0; i < func_params_count; i++) {
        if (strcmp(func_params[i]->_ast_val._var_decl._var_name, node->_ast_val._symbol._sym_name) == 0) {
            fprintf(f, "%%%s = add %s 0, %%%s\n", tmp, func_params[i]->_ast_val._var_decl._var_type._llvm_ir,
                func_params[i]->_ast_val._var_decl._var_name);
            return OK_OUTPUT;
        }
    }
    return KO_OUTPUT;
}

/**
 * @brief Generate the right line of LLVM IR with the AST type.
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 *
 * @return The final variable.
 */
char *
llvm_gen_value(ast_node_t *node, FILE *f)
{
    char *tmp = get_random_var_name();

    switch (node->_type) {
        case AST_LITERAL_INT:
            fprintf(f, "%%%s = add i32 0, %d\n", tmp,
                node->_ast_val._int_literal._value);
            break;
        case AST_CALL_SYM:
            llvm_call_sym(node, f, tmp);
            break;
        case AST_SYMBOL:
            if (generate_symbol_from_param(node, f, tmp) == OK_OUTPUT)
                break;
            fprintf(f, "%%%s = load i32, i32* %%%s\n", tmp,
                node->_ast_val._symbol._sym_name);
            break;
        case AST_BINARY_OP:
            llvm_math(node, f, tmp);
            break;
        case AST_STRING:
            llvm_string(node, f, tmp);
        default:
            break;
    }
    return tmp;
}

