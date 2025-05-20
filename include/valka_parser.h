/*
** VALKA PROJECT, 2025
** include/valka_parser.h
** File description:
** Valka parser header file
*/

#ifndef _VALKA_PARSER_H_
    #define _VALKA_PARSER_H_

    #include "misc/types.h"

    #define IDENTIFIER_ID_VAR 1
    #define IDENTIFIER_ID_FUNC 2

/**
 * @brief All token types.
 */
typedef enum {
    TOKEN_START,
    TOKEN_SYMBOL,
    TOKEN_IDENTIFIER,
    TOKEN_VAR_TYPE,
    TOKEN_FUNC,
    TOKEN_ASSIGN,
    TOKEN_INT_LITERAL,
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
 * @brief All AST types.
 */
typedef enum {
    AST_IDENTIFIER,
    AST_VAR_DECL,
    AST_ASSIGNMENT,
    AST_LITERAL_STRING,
    AST_LITERAL_INT,
    AST_BINARY_OP,
    AST_FUNCTION,
} ast_node_type_t;

/**
 * @brief Location mean the line and column of a syntax error for example.
 */
typedef struct location_s {
    uint32_t _line;
    uint32_t _col;
} location_t;

/**
 * @brief A token which contains everything we need to know.
 */
typedef struct token_s {
    const char *_start;
    uint32_t _length;
    location_t _loc;
    token_type_t _type;
    uint32_t _type_id;
    struct token_s *_next;
} token_t;

/**
 * @brief The main structure for the parsing of 1 file only.
 */
typedef struct {
    token_t *_head_list;
    token_t *_tail_list;
    uint32_t _current_index;
    location_t _current_loc;
    char *_buffer;
    uint32_t _buffer_size;
} parsing_src_file_t;

/**
 * @brief The ast_node_t structure which contains all sub AST and informations.
 */
typedef struct ast_node_s ast_node_t;

typedef struct ast_program_s ast_program_t;

/**
 * @brief One statement is basically 1 line.
 */
typedef struct ast_statement_s {
    ast_node_t *_ast_node;
    uint32_t _ast_id;
    struct ast_statement_s *_next;
} ast_statement_t;


/**
 * @brief ast_node_t, using union to make all NODE.
 */
struct ast_node_s {
    ast_node_type_t _type;
    location_t _loc;
    union {
        // Identifier -> if, var, function, ...
        struct {
            char *_name;
        } _identifier;
        // Int literal -> 15, 99, 191, ...
        struct {
            int _value;
        } _int_literal;
        // String -> "hello", "world", ...
        struct {
            char *_value;
        } _string;
        // Binary operation -> 10 + 5, 5 / 7, 8 % 8, ...
        struct {
            char *_op;
            ast_node_t *_left;
            ast_node_t *_right;
        } _binary_op;
        // Variable declaration -> var<i32> i = 5
        struct {
            char *_var_name;
            char *_type_value;
            ast_node_t *_value;
        } _var_decl;
        // Assignment -> i = 10
        struct {
            char *_var_name;
            ast_node_t *_value;
        } _assignment;
        // Function -> function main() { }
        struct {
            char *_func_name;
            ast_program_t *_func_content;
        } _function;
    } _ast_val;
};

/**
* @brief All statement is basically the whole source code.
*        The ast_program_t contains everything.
*/
struct ast_program_s {
    ast_statement_t *_statement_head;
    ast_statement_t *_statement_tail;
    uint32_t _statements_amount;
};

/*
 * Folder : src/parser/tokens/
 */
parsing_src_file_t *tokenize_source_code(char *filepath);
token_t *create_token(token_type_t type, const char *start, uint32_t length, location_t loc);
token_t *push_token(token_t **tail, token_t *token);

/*
 * Folder : src/parser/tokens/dispatch/
 */
parsing_src_file_t *alpha_token(parsing_src_file_t *p);
parsing_src_file_t *digit_token(parsing_src_file_t *p);
parsing_src_file_t *var_type_token(parsing_src_file_t *p);
parsing_src_file_t *assign_token(parsing_src_file_t *p);
parsing_src_file_t *semicolon_token(parsing_src_file_t *p);
parsing_src_file_t *brackets_token(parsing_src_file_t *p);

/*
 * Folder : src/parser/tokens/printer/
 */
void print_tokens(parsing_src_file_t *p);
void print_type_token(token_type_t type);

/*
 * Folder : src/parser/ast/
 */
ast_program_t *make_ast(parsing_src_file_t *p);
ast_node_t *dispatch_ast(token_t **current_token);
ast_statement_t *create_statement(ast_program_t *prg, ast_node_t *ast);
void move_token(token_t **current_token, int move_token);

/*
 * Folder : src/parser/ast/dispatch/
 */
ast_node_t *make_ast_var(token_t **current_token);
ast_node_t *make_ast_func(token_t **current_token);
ast_node_t *make_ast_int_literal(token_t **current_token);

/*
 * Folder : src/parser/ast/printer/
 */
void print_program(ast_program_t *prg);

#endif /* ifndef _VALKA_PARSER_H_ */
