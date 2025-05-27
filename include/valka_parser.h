/*
** VALKA PROJECT, 2025
** include/valka_parser.h
** File description:
** Valka parser header file
*/

#ifndef _VALKA_PARSER_H_
    #define _VALKA_PARSER_H_

    #include "misc/types.h"

extern uint32_t register_id;

/* All data types in Valka */

    #define T_I32 1
    #define T_BOOL 2
    #define T_CHAR 3
    #define T_VOID 4
    #define T_VARG 5
    #define T_CHAR_P 6
    #define T_BOOL_P 7
    #define T_I32_P 8

/* All condition operators in Valka */

    #define OP_EQUAL 1
    #define OP_GREATER_EQ 2
    #define OP_LOWER_EQ 3
    #define OP_GREATER 4
    #define OP_LOWER 5
    #define OP_NOT_EQUAL 6

/**
 * @brief The data type.
 */
typedef struct data_types_s {
    uint32_t _id;
    char _valka_ir[32];
    char _llvm_ir[32];
} data_types_t;

extern const data_types_t data_types[];

/**
 * @brief The condition operator.
 */
typedef struct condition_operator_s {
    char _operator[32];
    uint32_t _id;
} condition_operator_t;

extern const condition_operator_t condition_operators[];

    #define IS_VALID_DATA_TYPE(x) (x._id != 0)

    /* Types for somes AST */
    #define IDENTIFIER_ID_VAR 1
    #define IDENTIFIER_ID_FUNC 2
    #define IDENTIFIER_ID_RETURN 3
    #define IDENTIFIER_ID_IF 4

    #ifndef START_ENTRY_POINT
        #define START_ENTRY_POINT "main"
    #endif

    /* Some builtins */
    #ifndef SYSCALL_BUILTIN_NAME
        #define SYSCALL_BUILTIN_NAME "syscall"
    #endif

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
    TOKEN_CONDITION,
    TOKEN_END
} token_type_t;

/**
 * @brief All AST types.
 */
typedef enum {
    AST_IDENTIFIER,
    AST_VAR_DECL,
    AST_ASSIGNMENT,
    AST_LITERAL_INT,
    AST_BINARY_OP,
    AST_FUNCTION,
    AST_RETURN,
    AST_CALL_SYM,
    AST_SYMBOL,
    AST_STRING,
    AST_IF,
    AST_CONDITION,
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
    ast_program_t *_parent;
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
            char *_name_sym;
        } _string;
        // Binary operation -> 10 + 5, 5 / 7, 8 % 8, ...
        struct {
            char _op;
            ast_node_t *_left;
            ast_node_t *_right;
        } _binary_op;
        // If statement -> if (1 == 1) { }
        struct {
            ast_node_t *_condition;
            ast_program_t *_if_body;
            ast_program_t *_else_body;
        } _if_statement;
        // Variable declaration -> var<i32> i = 5
        struct {
            char *_var_name;
            data_types_t _var_type;
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
            data_types_t _return_data;
            ast_node_t **_params;
            uint32_t _params_count;
            ast_program_t *_func_content;
        } _function;
        // Call symbol -> hello()
        struct {
            char *_sym_name;
            uint32_t _args_count;
            ast_node_t **_args;
        } _call_sym;
        // Symbol -> hello
        struct {
            char *_sym_name;
        } _symbol;
        // Return -> return var or a ast_node_t
        struct {
            size_t _return_id;
            ast_node_t *_value;
            data_types_t _return_data;
            char *_sym_name;
        } _return;
        struct {
            ast_node_t *_node_a;
            uint32_t _op_id;
            ast_node_t *_node_b;
        } _condition;
    } _ast_val;
};

/**
 * @brief Binary operation types.
 */

    #ifndef OPERATORS_STR
        #define OPERATORS_STR "/+-*%"
    #endif

typedef struct bin_ope_s {
    char _operator;
    char _llvm_ir[32];
} bin_ope_t;

extern const bin_ope_t bin_operations[];

/**
 * @brief Functions prototypes declarations.
 */
typedef struct functions_prototype_s {
    char *_func_name;
    data_types_t _return;
    ast_node_t **_params;
} functions_prototype_t;

extern functions_prototype_t *prototypes;
extern uint32_t prototypes_count;

/**
* @brief All statement is basically the whole source code.
*        The ast_program_t contains everything.
*/
struct ast_program_s {
    functions_prototype_t *_prototypes;
    uint32_t _prototypes_count;
    ast_statement_t *_statement_head;
    ast_statement_t *_statement_tail;
    int32_t _statements_amount;
    ast_node_t *_parent;
};

/*
 * Folder : src/parser/tokens/
 */
parsing_src_file_t *tokenize_source_code(char *filepath);
token_t *create_token(token_type_t type, const char *start, uint32_t length, location_t loc);
token_t *push_token(token_t **tail, token_t *token);
bool_t is_start_of_expression(token_t *token);
bool_t is_call_sym(token_t *token);
bool_t is_valid_condition(const char *start);
token_t *get_next_token_after_call(token_t *node);

/*
 * Folder : src/parser/tokens/dispatch/
 */
parsing_src_file_t *alpha_token(parsing_src_file_t *p);
parsing_src_file_t *digit_token(parsing_src_file_t *p);
parsing_src_file_t *var_type_token(parsing_src_file_t *p);
parsing_src_file_t *assign_token(parsing_src_file_t *p);
parsing_src_file_t *semicolon_token(parsing_src_file_t *p);
parsing_src_file_t *brackets_token(parsing_src_file_t *p);
parsing_src_file_t *parents_token(parsing_src_file_t *p);
parsing_src_file_t *bin_operation_token(parsing_src_file_t *p);
parsing_src_file_t *comma_token(parsing_src_file_t *p);
parsing_src_file_t *string_token(parsing_src_file_t *p);
parsing_src_file_t *condition_token(parsing_src_file_t *p);

/*
 * Folder : src/parser/tokens/printer/
 */
void print_tokens(parsing_src_file_t *p);
void print_type_token(token_type_t type);

/*
 * Folder : src/parser/ast/
 */
ast_program_t *make_ast(parsing_src_file_t *p);
ast_node_t *dispatch_ast(token_t **current_token, ast_program_t *parent);
void move_token(token_t **current_token, int move_token);
ast_statement_t *create_statement(ast_program_t *prg, ast_node_t *ast);
ast_node_t *get_func_parent(ast_program_t *parent);

/*
 * Folder : src/parser/ast/dispatch/
 */
ast_node_t *make_ast_var(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_func(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_int_literal(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_return(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_bin_ope(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_expression(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_call_sym(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_symbol(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_string(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_if(token_t **current_token, ast_program_t *parent);
ast_node_t *make_ast_condition(token_t **current_token, ast_program_t *parent);

/*
 * Folder : src/parser/ast/printer/
 */
void print_program(ast_program_t *prg);

/*
 * Folder : src/parser/
 */
void add_function_prototype(ast_node_t *func_node);
functions_prototype_t get_prototype_from_name(const char *func_name);

/*
 * Folder : src/utils/data/
 */
data_types_t get_data_type(token_t *token);
data_types_t get_data_with_id(uint32_t id);
bin_ope_t get_operator_with_char(char op);

#endif /* ifndef _VALKA_PARSER_H_ */
