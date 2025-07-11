/*
** VALKA PROJECT, 2025
** src/parser/tokens/tokenizer
** File description:
** Main file for tokenizing the source code
*/

#include "valka.h"

/**
 * @brief Open the file path and return a structure containing the buffer.
 *
 * @param filepath      The file path
 *
 * @return The structure.
 */
static parsing_src_file_t *
open_src_filepath(char *filepath)
{
    parsing_src_file_t *p_src = MALLOC(sizeof(parsing_src_file_t));
    FILE *file_stream = NULL;
    location_t start_l = {1, 1};

    if (filepath == NULL)
        return NULL;
    file_stream = fopen(filepath, "r");
    fseek(file_stream, 0L, SEEK_END);
    p_src->_buffer_size = ftell(file_stream);
    p_src->_current_index = 0;
    p_src->_buffer = MALLOC(p_src->_buffer_size);
    rewind(file_stream);
    fread(p_src->_buffer, p_src->_buffer_size, 1, file_stream);
    fclose(file_stream);
    p_src->_current_loc = start_l;
    p_src->_head_list = create_token(TOKEN_START, p_src->_buffer, 0, start_l);
    p_src->_tail_list = p_src->_head_list;
    return p_src;
}

/**
 * @brief Dispatch and use the right function for the current token.
 *
 * @param p            The structure parsing of the current file
 */
static parsing_src_file_t *
dispatch_tokenizer(parsing_src_file_t *p)
{
    char c = p->_buffer[p->_current_index];

    if (c == '@')
        return misc_token(p);
    if (is_valid_condition(&p->_buffer[p->_current_index]))
        return condition_token(p);
    if (isdigit(c) || (c == '-' && isdigit(p->_buffer[p->_current_index + 1])))
        return digit_token(p);
    if (strchr(OPERATORS_STR, c) != NULL)
        return bin_operation_token(p);
    if (c == ',')
        return comma_token(p);
    if (c == '.')
        return dot_token(p);
    if (c == '#')
        return cast_token(p);
    if (c == '\"')
        return string_token(p);
    if (c == '<')
        return var_type_token(p);
    if (c == '=')
        return assign_token(p);
    if (c == ';')
        return semicolon_token(p);
    if (c == '{' || c == '}')
        return brackets_token(p);
    if (c == '[' || c == ']')
        return square_brackets_token(p);
    if (c == '(' || c == ')')
        return parents_token(p);
    if (isalpha(c) || c == '_')
        return alpha_token(p);
    p->_current_index++;
    return p;
}

/**
 * @brief Do a full tokenizing of 1 file using his filepath.
 *
 * @param filepath      The file path
 *
 * @return The final tokenized structure.
 */
parsing_src_file_t *
tokenize_source_code(char *filepath)
{
    parsing_src_file_t *p = open_src_filepath(filepath);

    if (p == NULL)
        return NULL;
    create_base_definitions();
    prepass_buffer(p);
    while (p->_current_index < p->_buffer_size) {
        dispatch_tokenizer(p);
    }
    push_token(&p->_tail_list, create_token(TOKEN_END, p->_buffer, 0,
        p->_current_loc));
    return p;
}
