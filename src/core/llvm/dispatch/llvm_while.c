/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_while
** File description:
** LLVM for while declaration
*/

#include "valka.h"

/**
 * @brief LLVM while declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_while(ast_node_t *node, FILE *f)
{
    const char *loop_cond_label = get_random_var_name();
    const char *loop_body_label = get_random_var_name();
    const char *loop_end_label  = get_random_var_name();
    char *cond_reg = get_random_var_name();

    fprintf(f, "br label %%%s\n", loop_cond_label);

    fprintf(f, "\n%s:\n", loop_cond_label);
    llvm_condition(node->_ast_val._for_statement._condition_statement, f, cond_reg);
    fprintf(f, "br i1 %%%s, label %%%s, label %%%s\n", cond_reg, loop_body_label, loop_end_label);

    fprintf(f, "\n%s:\n", loop_body_label);
    generate_llvm_global(f, node->_ast_val._for_statement._for_body);
    fprintf(f, "br label %%%s\n", loop_cond_label);

    fprintf(f, "%s:\n", loop_end_label);
    return OK_OUTPUT;
}
