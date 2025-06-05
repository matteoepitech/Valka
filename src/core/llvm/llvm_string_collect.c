/*
** VALKA PROJECT, 2025
** src/core/llvm/llvm_string_symbols
** File description:
** LLVM string symbols
*/

#include "valka.h"

/**
 * @brief Collect all strings.
 *
 * @param prg           The program ASTs
 * @param f             The FILE to write in
 */
void
collect_all_strings(ast_program_t *prg, FILE *f)
{
    ast_statement_t *statement = prg->_statement_head;

    for (; statement != NULL; statement = statement->_next)
        collect_strings(statement->_ast_node, f);
    fprintf(f, "\n");
}

/**
 * @brief Collect every strings and write them in the top of the file.
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 */
void
collect_strings(ast_node_t *node, FILE *f)
{
    if (node == NULL || f == NULL)
        return;
    switch (node->_type) {
        case AST_STRING: {
            fprintf(f, "@%s = private constant [%lu x i8] c\"%s\\00\"\n",
                node->_ast_val._string._name_sym,
                (unsigned long) strlen(node->_ast_val._string._value) + 1,
                node->_ast_val._string._value);
        } break;
        case AST_VAR_DECL:
            collect_strings(node->_ast_val._var_decl._value, f);
            break;
        case AST_ASSIGNMENT:
            collect_strings(node->_ast_val._assignment._value, f);
            break;
        case AST_BINARY_OP:
            collect_strings(node->_ast_val._binary_op._left, f);
            collect_strings(node->_ast_val._binary_op._right, f);
            break;
        case AST_FUNCTION: {
            for (uint32_t i = 0; i < node->_ast_val._function._params_count; i++)
                collect_strings(node->_ast_val._function._params[i], f);
            for (ast_statement_t *tmp = node->_ast_val._function._func_content->_statement_head; tmp != NULL; tmp = tmp->_next) {
                collect_strings(tmp->_ast_node, f);
            }
        } break;
        case AST_CALL_SYM: {
            for (uint32_t i = 0; i < node->_ast_val._call_sym._args_count; i++)
                collect_strings(node->_ast_val._call_sym._args[i], f);
        } break;
        case AST_RETURN:
            collect_strings(node->_ast_val._return._value, f);
            break;
        case AST_IF:
            collect_strings(node->_ast_val._if_statement._condition, f);
            for (ast_statement_t *tmp = node->_ast_val._if_statement._if_body->_statement_head; tmp != NULL; tmp = tmp->_next) {
                collect_strings(tmp->_ast_node, f);
            }
            for (ast_statement_t *tmp = node->_ast_val._if_statement._else_body->_statement_head; tmp != NULL; tmp = tmp->_next) {
                collect_strings(tmp->_ast_node, f);
            }
            break;

        case AST_FOR:
            collect_strings(node->_ast_val._for_statement._init_statement, f);
            collect_strings(node->_ast_val._for_statement._condition_statement, f);
            collect_strings(node->_ast_val._for_statement._update_statement, f);
            for (ast_statement_t *tmp = node->_ast_val._for_statement._for_body->_statement_head; tmp != NULL; tmp = tmp->_next) {
                collect_strings(tmp->_ast_node, f);
            }
            break;
        
        case AST_WHILE:
            collect_strings(node->_ast_val._for_statement._condition_statement, f);
            for (ast_statement_t *tmp = node->_ast_val._for_statement._for_body->_statement_head; tmp != NULL; tmp = tmp->_next) {
                collect_strings(tmp->_ast_node, f);
            }
            break;

        case AST_CONDITION:
            collect_strings(node->_ast_val._condition._node_a, f);
            collect_strings(node->_ast_val._condition._node_b, f);
            break;

        case AST_INDEX:
            for (uint32_t i = 0; i < node->_ast_val._index._index_count; i++)
                collect_strings(node->_ast_val._index._indices[i], f);
            collect_strings(node->_ast_val._index._sym, f);
            break;

        case AST_FIELD:
            collect_strings(node->_ast_val._field._symbol, f);

        default:
            break;
    }
}
