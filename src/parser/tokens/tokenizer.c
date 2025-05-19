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
parsing_src_file_t *dispatch_tokenizer(parsing_src_file_t *p)
{
    char c = p->_buffer[p->_current_index];

    if (c == '<')
        return var_type_token(p);
    if (c == '=')
        return assign_token(p);
    if (isalpha(c) || c == '_')
        return alpha_token(p);
    if (isdigit(c))
        return digit_token(p);
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
    while (p->_current_index < p->_buffer_size) {
        dispatch_tokenizer(p);
    }
    return p;
}
