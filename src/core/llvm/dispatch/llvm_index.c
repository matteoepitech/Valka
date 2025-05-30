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
    fprintf(f, "NO INDEX!\n");
    return OK_OUTPUT;
}
