/*
** VALKA PROJECT, 2025
** src/parser/tokens/printer/print_tokens
** File description:
** Print tokens
*/

#include "valka.h"

/**
 * @brief Print the type of the token.
 *
 * @param type   The type
 */
void
print_type_token(token_type_t type)
{
    static const char *type_names[] = {
        "START", "SYMBOL", "IDENTIFIER", "VAR_TYPE", "FUNCTION", "ASSIGN",
        "INT_LITERAL", "STRING", "COMMENT_BIG", "COMMENT_SMALL", "PARENT_OPEN",
        "PARENT_CLOSE", "BRACKET_OPEN", "BRACKET_CLOSE", "SQUARE_BRACKET_OPEN",
        "SQUARE_BRACKET_CLOSE", "MATH_OPERATOR", "SEMICOLON", "COMMA",
        "CONDITION", "CAST", "END"
    };
    if (type < 0 || type >= (sizeof(type_names) / sizeof(type_names[0]))) {
        printf("UNKNOWN_TOKEN_TYPE");
    } else {
        printf("%s", type_names[type]);
    }
    fflush(stdout);
}

/**
 * @brief Print tokens for debugging ONLY.
 *
 * @param p     The parsing_src_file_t
 */
void
print_tokens(parsing_src_file_t *p)
{
    static const char *types_color[] = {"\033[33m", "\033[32m", "\033[31m",
        "\033[34m"
    };
    size_t i = 0;
    token_t *tmp = p->_head_list;

    while (tmp != NULL) {
        printf("%s", types_color[i % 4]);
        print_type_token(tmp->_type);
        if (tmp->_type == TOKEN_IDENTIFIER || tmp->_type == TOKEN_CONDITION)
            printf(" id (%d)", tmp->_type_id);
        printf(": \033[0m");
        fflush(stdout);
        for (uint32_t i = 0; i < tmp->_length; i++) {
            printf("%c", tmp->_start[i]);
        }
        printf("\n");
        tmp = tmp->_next;
        i++;
    }
}
