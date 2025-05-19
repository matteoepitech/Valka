/*
** VALKA PROJECT, 2025
** src/parser/tokens/printer/print_tokens
** File description:
** Print tokens
*/

#include "valka.h"
#include "valka_parser.h"

/**
 * @brief Print the type of the token.
 *
 * @param type   The type
 */
void
print_type_token(token_type_t type)
{
    static const char *types_names[] = {"START", "SYMBOL", "IDENTIFIER",
        "VAR_TYPE", "FUNCTION", "ASSIGN", "INT32 (LITERAL)", "END"
    };

    printf("%s", types_names[type]);
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
