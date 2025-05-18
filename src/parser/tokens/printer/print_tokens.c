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
    static const char *types_names[] = {"START", "SYMBOL", "END"};
    token_t *tmp = p->_head_list;

    while (tmp != NULL) {
        printf("%s: ", types_names[tmp->_type]);
        for (uint32_t i = 0; i < tmp->_length; i++) {
            printf("%c", tmp->_start[i]);
        }
        printf("\n");
        tmp = tmp->_next;
    }
}
