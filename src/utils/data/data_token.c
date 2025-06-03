/*
** VALKA PROJECT, 2025
** src/core/llvm/data_token
** File description:
** Get data types from tokens
*/

#include "valka.h"

/**
 * @brief Search for a primitive data type in the data_types array.
 *
 * @param inside        The type string to search for
 * @param ptr_level     The pointer level to apply
 *
 * @return The found data type or zero-initialized type if not found.
 */
static data_types_t
find_primitive_type(const char *inside, int ptr_level,
    int array_dims[MAX_INDICES_DEPTH], int array_count)
{
    data_types_t result = {0};
    uint32_t length = 0;
    const char *decl = NULL;

    while (inside[length] != '\0' && inside[length] != '[')
        length++;
    for (int i = 0; data_types[i]._id != 0; i++) {
        decl = data_types[i]._valka_ir;
        if (strlen(decl) == length && strncmp(inside, decl, length) == 0) {
            result = data_types[i];
            result._ptr_level = ptr_level;
            result._array_count = array_count;
            for (int j = 0; j < array_count; j++)
                result._array_dims[j] = array_dims[j];
            return result;
        }
    }
    return (data_types_t){0};
}

/**
 * @brief Extract and prepare the token content for type parsing.
 *
 * @param token         The token to extract from
 * @param inside_len    Pointer to store the extracted content length
 *
 * @return The extracted content string or NULL if invalid.
 */
static char *
extract_token_content(token_t *token, int *inside_len)
{
    if (token == NULL || token->_length < 3)
        return NULL;    
    *inside_len = token->_length - 2;
    return strndup_valka(&token->_start[1], *inside_len);
}

/**
 * @brief Count and remove pointer levels from the type string.
 *
 * @param inside        The type string to process
 * @param inside_len    Pointer to the string length
 *
 * @return The number of pointer levels found.
 */
static int
extract_pointer_level(char *inside, int *inside_len)
{
    int ptr_level = 0;
    
    for (int i = *inside_len - 1; i >= 0 && inside[i] == '*'; i--) {
        ptr_level++;
        inside[i] = '\0';
        (*inside_len)--;
    }
    return ptr_level;
}

/**
 * @brief Extract array dimensions from the type string.
 *
 * @param inside        The type string to process
 * @param inside_len    Pointer to the string length
 * @param dims          Array to store found dimensions
 *
 * @return Number of dimensions extracted.
 */
static int
extract_array_dimensions(char *inside, int *inside_len, int *dims)
{
    int dim_count = 0;
    int end = 0;
    int tmp = 0;
    char *num_str = NULL;

    for (int i = *inside_len - 1; i >= 0; ) {
        if (inside[i] != ']')
            break;
        end = i;
        while (i >= 0 && inside[i] != '[')
            i--;
        if (i < 0)
            break;
        inside[end] = '\0';
        num_str = &inside[i + 1];
        if (atoi(num_str) <= 0 || dim_count >= MAX_INDICES_DEPTH)
            break;
        dims[dim_count++] = atoi(num_str);
        inside[i] = '\0';
        *inside_len = i;
        i--;
    }
    for (int j = 0; j < dim_count / 2; j++) {
        tmp = dims[j];
        dims[j] = dims[dim_count - 1 - j];
        dims[dim_count - 1 - j] = tmp;
    }
    return dim_count;
}

/**
 * @brief Create a struct data type from the type string.
 *
 * @param inside        The type string containing struct declaration
 * @param ptr_level     The pointer level to apply
 *
 * @return The struct data type.
 */
static data_types_t
create_struct_type(const char *inside, int ptr_level)
{
    data_types_t result = {0};
    char *struct_name = (char *)inside + 7;
    
    result._bits_sz = 0;
    result._id = T_STRUCT;
    result._ptr_level = ptr_level;
    strncpy(result._valka_ir, inside, sizeof(result._valka_ir) - 1);
    result._valka_ir[sizeof(result._valka_ir) - 1] = '\0';
    snprintf(result._llvm_ir, sizeof(result._llvm_ir), "%%%s", struct_name);
    return result;
}

/**
 * @brief Check if the type string represents a struct type.
 *
 * @param inside        The type string to check
 *
 * @return True if it's a struct type, false otherwise.
 */
static bool_t
is_struct_type(const char *inside)
{
    return strncmp("struct ", inside, 7) == 0;
}

/**
 * @brief Get the token type of the data if the data is existing.
 *
 * @param token         The token
 *
 * @return The corresponding data type.
 */
data_types_t
get_data_type_from_token(token_t *token)
{
    int inside_len = 0;
    char *inside = extract_token_content(token, &inside_len);
    int ptr_level = 0;
    int array_dims[MAX_INDICES_DEPTH] = {0};
    int array_count = 0;
    data_types_t result = {0};

    if (inside == NULL)
        return result;
    array_count = extract_array_dimensions(inside, &inside_len, array_dims);
    ptr_level = extract_pointer_level(inside, &inside_len);
    result = find_primitive_type(inside, ptr_level, array_dims, array_count);
    if (result._id != 0) {
        result._array_count = array_count;
        for (int i = 0; i < array_count; i++)
            result._array_dims[i] = array_dims[i];
        return result;
    }
    if (is_struct_type(inside)) {
        result = create_struct_type(inside, ptr_level);
        result._array_count = array_count;
        for (int i = 0; i < array_count; i++)
            result._array_dims[i] = array_dims[i];
        return result;
    }
    return (data_types_t){0};
}
