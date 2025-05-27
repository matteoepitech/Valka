/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_if
** File description:
** LLVM for if declaration
*/

#include "valka.h"

/**
 * @brief LLVM if declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_if(ast_node_t *node, FILE *f)
{
    char *cond_reg = get_random_var_name();
    const char *if_true_label = "if_true";//get_random_var_name();
    const char *if_false_label = "if_false";//get_random_var_name();
    const char *if_end_label = "if_end";//get_random_var_name();

    llvm_condition(node->_ast_val._if_statement._condition, f, cond_reg);
    fprintf(f, "br i1 %%%s, label %%%s, label %%%s\n", cond_reg, if_true_label, if_false_label);
    fprintf(f, "%s:\n", if_true_label);
    generate_llvm_global(f, node->_ast_val._if_statement._if_body);
    fprintf(f, "br label %%%s\n", if_end_label);
    fprintf(f, "%s:\n", if_false_label);
    if (node->_ast_val._if_statement._else_body)
        generate_llvm_global(f, node->_ast_val._if_statement._else_body);
    fprintf(f, "br label %%%s\n", if_end_label);
    fprintf(f, "%s:\n", if_end_label);
    return OK_OUTPUT;
}
