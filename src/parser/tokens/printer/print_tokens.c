/*
** VALKA PROJECT, 2025
** src/parser/tokens/printer/print_tokens
** File description:
** Print tokens
*/

#include "valka.h"

/**
 * @brief Print tokens for debugging ONLY.
 *
 * @param p     The parsing_src_file_t
 */
void
print_tokens(parsing_src_file_t *p)
{
    static const char *types_names[] = {"START", "SYMBOL", "IDENTIFIER",
        "VAR_TYPE", "FUNCTION", "ASSIGN", "INT32 (LITERAL)", "END"
    };
    static const char *types_color[] = {"\033[33m", "\033[32m", "\033[31m",
        "\033[34m"
    };
    size_t i = 0;
    token_t *tmp = p->_head_list;

    while (tmp != NULL) {
        printf("%s%s: \033[0m", types_color[i % 4], types_names[tmp->_type]);
        for (uint32_t i = 0; i < tmp->_length; i++) {
            printf("%c", tmp->_start[i]);
        }
        printf("\n");
        tmp = tmp->_next;
        i++;
    }
}
