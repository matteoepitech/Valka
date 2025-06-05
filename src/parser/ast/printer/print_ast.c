/*
** VALKA PROJECT, 2025
** src/parser/ast/printer/print_ast
** File description:
** Print one AST
*/

#include "valka.h"
#include "valka_parser.h"

// @TODO remove this.
static void print_ast(ast_node_t *node, int indent);

/**
 * @brief Print indentation spaces for pretty-printing the AST.
 *
 * @param indent        Number of indentation levels (2 spaces).
 */
static void
print_indent(int indent)
{
    for (int i = 0; i < indent; i++)
        printf("  ");
}

/**
 * @brief Print the content of the function.
 *
 * @param prg           The function content called prg.
 */
static void
print_function_body(ast_program_t *prg, int indent)
{
    ast_statement_t *current = NULL;

    if (prg->_statements_amount == -1) {
        print_indent(indent);
        fflush(stdout);
        printf(COLOR_YELLOW "This is an declaration of function.\n" COLOR_RESET);
        return;
    }
    if (prg == NULL || prg->_statement_head == NULL) {
        print_indent(indent);
        fflush(stdout);
        fprintf(stderr, COLOR_RED "(empty function body)\n" COLOR_RESET);
        return;
    }
    current = prg->_statement_head;
    while (current != NULL) {
        print_indent(indent - 1);
        printf(COLOR_CYAN "  [Statement %u]\n" COLOR_RESET, current->_ast_id);
        print_ast(current->_ast_node, indent);
        current = current->_next;
    }
}

/**
 * @brief Print the content symbols of a function
 *
 * @param func
 * @param indent
 */
static void
print_content_symbol(ast_program_t *prg, int indent)
{
    for (uint32_t i = 0; i < prg->_content_symbols_count; i++) {
        print_indent(indent);
        printf(COLOR_RED "Var : " COLOR_RESET "%s" COLOR_RED " with type %s\n",
            prg->_content_symbols[i]->_ast_val._var_decl._var_name,
            prg->_content_symbols[i]->_ast_val._var_decl._var_type._valka_ir
        );
    }
}

/**
 * @brief Recursively print a single AST node and its children with
 *        indentation.
 *
 * @param node          The AST node to print.
 * @param indent        Indentation level for pretty-printing.
 */
static void
print_ast(ast_node_t *node, int indent)
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
            printf("Int literal: %d\n", node->_ast_val._int_literal._value);
            break;
        
        case AST_LITERAL_FLOAT:
            printf("Float literal: %f\n", node->_ast_val._float_literal._value);
            break;

        case AST_STRING:
            printf("String: \"%s\"\n", node->_ast_val._string._value);
            break;

        case AST_INDEX:
            printf("Index for:\n");
            print_ast(node->_ast_val._index._sym, indent + 1);
            print_indent(indent); 
            printf("Indices (%zu):\n", node->_ast_val._index._index_count);
            for (size_t i = 0; i < node->_ast_val._index._index_count; i++) {
                print_indent(indent + 1);
                printf("[%zu]:\n", i);
                print_ast(node->_ast_val._index._indices[i], indent + 2);
            }
            break;

        case AST_FIELD:
            printf("Field for:\n");
            print_ast(node->_ast_val._field._symbol, indent + 1);
            print_indent(indent + 2);
            printf("field -> %s\n", node->_ast_val._field._field_name);
            break;
        

        case AST_BINARY_OP:
            printf("Binary operation: %c\n", node->_ast_val._binary_op._op);
            print_indent(indent);
            printf("Left:\n");
            print_ast(node->_ast_val._binary_op._left, indent + 1);
            print_indent(indent);
            printf("Right:\n");
            print_ast(node->_ast_val._binary_op._right, indent + 1);
            break;

        case AST_VAR_DECL:
            printf("Var decl: <%s> %s\n", get_write_data_type(node->_ast_val._var_decl._var_type, FALSE),
                node->_ast_val._var_decl._var_name);
            print_indent(indent);
            printf("Value:\n");
            print_ast(node->_ast_val._var_decl._value, indent + 1);
            break;

        case AST_ASSIGNMENT:
            printf("Assignment:\n");
            print_ast(node->_ast_val._assignment._assigned, indent + 1);
            print_indent(indent);
            printf("Value:\n");
            print_ast(node->_ast_val._assignment._value, indent + 1);
            break;

        case AST_FUNCTION:
            printf("Function: %s type (%s)\n", node->_ast_val._function._func_name, node->_ast_val._function._return_data._valka_ir);
            if (node->_ast_val._function._params_count == 0) {
                print_function_body(node->_ast_val._function._func_content, indent + 1);
                print_content_symbol(node->_ast_val._function._func_content, indent + 1);
                break;
            }
            print_indent(indent + 1);
            printf("Parameters:\n");
            for (uint32_t i = 0; i < node->_ast_val._function._params_count; i++) {
                print_indent(indent + 1);
                printf("- %s\n",
                    get_write_data_type(node->_ast_val._function._params[i]->_ast_val._var_decl._var_type, FALSE));
            }
            print_function_body(node->_ast_val._function._func_content, indent + 1);
            print_content_symbol(node->_ast_val._function._func_content, indent + 1);
            break;

        case AST_STRUCT:
            printf("Structure %s:\n", node->_ast_val._struct._struct_name);
            print_indent(indent + 1);
            printf("Fields:\n");
            for (uint32_t i = 0; i < node->_ast_val._struct._fields_count; i++) {
                print_indent(indent + 2);
                printf("- %s (%s)\n", node->_ast_val._struct._fields[i]->_ast_val._var_decl._var_name,
                    get_write_data_type(node->_ast_val._struct._fields[i]->_ast_val._var_decl._var_type, FALSE));
            }
            break;

        case AST_RETURN:
            printf("Return value:\n");
            print_ast(node->_ast_val._return._value, indent + 1);
            break;

        case AST_IF:
            printf("If statement:\n");
            print_ast(node->_ast_val._if_statement._condition, indent);
            print_indent(indent + 1);
            printf("IF BODY :\n");
            print_function_body(node->_ast_val._if_statement._if_body, indent + 2);
            print_indent(indent + 1);
            printf("ELSE BODY :\n");
            print_function_body(node->_ast_val._if_statement._else_body, indent + 2);
            break;

        case AST_FOR:
            printf("For statement:\n");
            print_indent(indent + 1);
            printf("Init statement:\n");
            print_ast(node->_ast_val._for_statement._init_statement, indent + 2);
            print_indent(indent + 1);
            printf("Condition statement:\n");
            print_ast(node->_ast_val._for_statement._condition_statement, indent + 2);
            print_indent(indent + 1);
            printf("Update statement:\n");
            print_ast(node->_ast_val._for_statement._update_statement, indent + 2);
            print_indent(indent + 1);
            printf("For body:\n");
            print_function_body(node->_ast_val._for_statement._for_body, indent + 2);
            break;
        
        case AST_WHILE:
            printf("While statement:\n");
            print_indent(indent + 1);
            printf("Condition statement:\n");
            print_ast(node->_ast_val._for_statement._condition_statement, indent + 2);
            print_indent(indent + 1);
            printf("While body:\n");
            print_function_body(node->_ast_val._for_statement._for_body, indent + 2);
            break;

        case AST_CONDITION:
            for (int i = 0; condition_operators[i]._id != 0; i++) {
                if (condition_operators[i]._id == node->_ast_val._condition._op_id) {
                    printf("Condition : %s\n", condition_operators[i]._operator);
                    break;
                }
            }
            print_ast(node->_ast_val._condition._node_a, indent + 1);
            print_ast(node->_ast_val._condition._node_b, indent + 1);
            break;
        
        case AST_CALL_SYM:
            printf("Call to %s", node->_ast_val._call_sym._sym_name);
            if (node->_ast_val._call_sym._args_count == 0) {
                printf("()\n");
                break;
            }
            printf("\n");
            print_indent(indent);
            printf("(\n");
            for (uint32_t i = 0; i < node->_ast_val._call_sym._args_count; i++) {
                print_ast(node->_ast_val._call_sym._args[i], indent + 1);
            }
            print_indent(indent);
            printf(")\n");
            break;
        
        case AST_SYMBOL:
            printf("Symbol %s\n", node->_ast_val._symbol._sym_name);
            break;

        case AST_CAST:
            printf("Cast to : %s\n", node->_ast_val._cast._cast_type._llvm_ir);
            print_ast(node->_ast_val._cast._val, indent + 1);
            break;

        default:
            printf("Unknown AST node type: %d\n", node->_type);
            break;
    }
}

/**
 * @brief Print the full program's AST, statement by statement.
 *
 * @param prg           Pointer to the AST program structure.
 */
void
print_program(ast_program_t *prg)
{
    ast_statement_t *current = NULL;

    if (prg == NULL || prg->_statement_head == NULL) {
        fprintf(stderr, "(null program)\n");
        return;
    }
    current = prg->_statement_head;
    while (current != NULL) {
        printf("\nStatement %u:\n", current->_ast_id);
        print_ast(current->_ast_node, 1);
        current = current->_next;
    }
}
