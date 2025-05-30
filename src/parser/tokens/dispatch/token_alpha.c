/*
** VALKA PROJECT, 2025
** src/parser/tokens/dispatch/token_alpha
** File description:
** Token alpha
*/

#include "valka.h"

/**
 * @brief If this is a identifier then we swap the TOKEN type.
 *
 * @param token         The token
 * @param p             The parsing src file structure
 *
 * @return The parsing src file structure.
 */
static parsing_src_file_t *
check_identifier(token_t *token, parsing_src_file_t *p)
{
    static const char *identifiers[] = {"var", "function", "return", "if",
        "for", "while", NULL
    };
    static const int identifiers_id[] = {IDENTIFIER_ID_VAR,
        IDENTIFIER_ID_FUNC, IDENTIFIER_ID_RETURN, IDENTIFIER_ID_IF,
        IDENTIFIER_ID_FOR, IDENTIFIER_ID_WHILE, -1
    };

    if (token == NULL)
        return p;
    for (size_t i = 0; identifiers[i] != NULL; i++) {
        if (strncmp(token->_start, identifiers[i], token->_length) == 0 &&
            strlen(identifiers[i]) == token->_length) {
            token->_type = TOKEN_IDENTIFIER;
            token->_type_id = identifiers_id[i];
            return p;
        }
    }
    return p;
}

/**
 * @brief Alpha token dispatch.
 *
 * @param p             The parsing src file structure
 *
 * @return The parsing src file structure.
 */
parsing_src_file_t *
alpha_token(parsing_src_file_t *p)
{
    const char *start = &p->_buffer[p->_current_index];
    size_t i = p->_current_index;
    size_t length = 0;
    token_t *token = NULL;

    while (i < p->_buffer_size &&
        (isalpha(p->_buffer[i]) || p->_buffer[i] == '_' ||
        isdigit(p->_buffer[i]))) {
        i++;
    }
    length = i - p->_current_index;
    token = create_token(TOKEN_SYMBOL, start, length, p->_current_loc);
    push_token(&p->_tail_list, token);
    p->_current_index = i;
    return check_identifier(token, p);
}
