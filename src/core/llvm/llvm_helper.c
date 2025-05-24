/*
** VALKA PROJECT, 2025
** src/core/llvm/llvm_helper
** File description:
** LLVM helper
*/

#include "valka.h"

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
            fprintf(f, "%%%s = load i32, i32* %%%s\n", tmp,
                node->_ast_val._symbol._sym_name);
            break;
        case AST_BINARY_OP:
            tmp = llvm_math(node, f);
            break;
        default:
            break;
    }
    return tmp;
}

