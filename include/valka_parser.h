/*
** VALKA PROJECT, 2025
** include/valka_parser.h
** File description:
** Valka parser header file
*/

#ifndef _VALKA_PARSER_H_
    #define _VALKA_PARSER_H_

    #include "misc/types.h"

/**
 * @brief Location mean the line and column of a syntax error for example.
 */
typedef struct location_s {
    uint32_t _line;
    uint32_t _col;
} location_t;

/**
 * @brief All token types.
 */
typedef enum {
    TOKEN_START,
    TOKEN_IDENTIFIER,
    TOKEN_FUNC,
    TOKEN_SYMBOL,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_COMMENT_BIG,
    TOKEN_COMMENT_SMALL,
    TOKEN_PARENT_OPEN,
    TOKEN_PARENT_CLOSE,
    TOKEN_BRACKET_OPEN,
    TOKEN_BRACKET_CLOSE,
    TOKEN_SQUARE_BRACKET_OPEN,
    TOKEN_SQUARE_BRACKET_CLOSE,
    TOKEN_MATH_OPERATOR,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_END
} token_type_t;

/**
 * @brief A token which contains everything we need to know.
 */
typedef struct token_s {
    const char *_start;
    uint32_t _length;
    location_t _loc;
    token_type_t _type;
    struct token_s *_next;
} token_t;

#endif /* ifndef _VALKA_PARSER_H_ */
