/*
** VALKA PROJECT, 2025
** src/core/llvm/llvm_manager
** File description:
** LLVM Manager
*/

#include "valka.h"

/**
 * @brief Dispatch the LLVM generating to get the right function.
 *
 * @param f             The FILE
 * @param cur           The current statement
 *
 * @return Everything worked?
 */
uint8_t
dispatch_llvm(FILE *f, ast_statement_t *cur)
{
    ast_node_t *node = cur->_ast_node;

    switch (node->_type) {
        case AST_ASSIGNMENT:
            return llvm_assign(node, f);
        case AST_IF:
            return llvm_if(node, f);
        case AST_FOR:
            return llvm_for(node, f);
        case AST_WHILE:
            return llvm_while(node, f);
        case AST_CALL_SYM:
            return llvm_call_sym(node, f, NULL);
        case AST_VAR_DECL:
            return llvm_var(node, f);
        case AST_FUNCTION:
            return llvm_func(node, f);
        case AST_STRUCT:
            return llvm_struct(node, f);
        case AST_RETURN:
            return llvm_return(node, f);
        default:
            return KO_OUTPUT;
    }
}

/**
 * @brief Create the LLVM file.
 *
 * @return The LLVM file opened.
 */
FILE *
create_llvm(void)
{
    FILE *llvm_out = fopen("out.ll", "w");

    if (llvm_out == NULL) {
        PERROR("Cannot create out.ll");
        return NULL;
    }
    return llvm_out;
}

/**
 * @brief Close the LLVM.
 *
 * @param f              The FILE
 *
 * @return Status of the operation.
 */
uint8_t
close_llvm(FILE *f)
{
    if (f == NULL)
        return KO_OUTPUT;
    fclose(f);
    return OK_OUTPUT;
}

/**
 * @brief Generate the LLVM.
 *
 * @param f             The FILE
 * @param prg           The program
 */
void
generate_llvm_global(FILE *f, ast_program_t *prg)
{
    ast_statement_t *cur = prg->_statement_head;

    while (cur) {
        if (dispatch_llvm(f, cur) == KO_OUTPUT)
            break;
        cur = cur->_next;
    }
}
