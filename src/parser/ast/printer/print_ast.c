/*
** VALKA PROJECT, 2025
** src/parser/ast/printer/print_ast
** File description:
** Print one AST
*/

#include "valka.h"

static void print_indent(int indent)
{
    for (int i = 0; i < indent; i++)
        printf("  ");
}

void print_ast(ast_node_t *node, int indent)
{
    if (node == NULL) {
        print_indent(indent);
        printf("(null)\n");
        return;
    }

    print_indent(indent);
    switch (node->_type) {
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->_ast_val._identifier._name);
            break;
        case AST_LITERAL_INT:
            printf("IntLiteral: %d\n", node->_ast_val._int_literal._value);
            break;
        case AST_LITERAL_STRING:
            printf("String: \"%s\"\n", node->_ast_val._string._value);
            break;
        case AST_BINARY_OP:
            printf("BinaryOp: %s\n", node->_ast_val._binary_op._op);
            print_indent(indent);
            printf("Left:\n");
            print_ast(node->_ast_val._binary_op._left, indent + 1);
            print_indent(indent);
            printf("Right:\n");
            print_ast(node->_ast_val._binary_op._right, indent + 1);
            break;
        case AST_VAR_DECL:
            printf("VarDecl: %s %s\n", node->_ast_val._var_decl._type_value, node->_ast_val._var_decl._var_name);
            print_indent(indent);
            printf("Value:\n");
            print_ast(node->_ast_val._var_decl._value, indent + 1);
            break;
        case AST_ASSIGNMENT:
            printf("Assignment: %s\n", node->_ast_val._assignment._var_name);
            print_indent(indent);
            printf("Value:\n");
            print_ast(node->_ast_val._assignment._value, indent + 1);
            break;
        default:
            printf("Unknown AST node type: %d\n", node->_type);
            break;
    }
}

void print_program(ast_program_t *prg)
{
    ast_statement_t *current = NULL;

    if (prg == NULL || prg->_statement_head == NULL) {
        fprintf(stderr, "(null program)\n");
        return;
    }
    current = prg->_statement_head;
    while (current != NULL) {
        printf("Statement %u:\n", current->_ast_id);
        print_ast(current->_ast_node, 1);
        current = current->_next;
    }
}
