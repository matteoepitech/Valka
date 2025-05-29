/*
** VALKA PROJECT, 2025
** src/utils/data/data_helper
** File description:
** Data helper functions
*/

#include "valka.h"
#include "valka_parser.h"

/**
 * @brief Get the data with ID.
 *
 * @param id            The ID
 *
 * @return The data.
 */
data_types_t
get_data_with_id(uint32_t id)
{
    for (int i = 0; data_types[i]._id != 0; i++) {
        if (data_types[i]._id == id)
            return data_types[i];
    }
    return (data_types_t) {0};
}

/**
 * @brief Get the token type of the data if the data is existing.
 *
 * @param token         The token
 */
data_types_t
get_data_type(token_t *token)
{
    if (token == NULL)
        return (data_types_t) {0};
    for (int i = 0; data_types[i]._id != 0; i++) {
        if (strncmp(&token->_start[1], data_types[i]._valka_ir,
            token->_length - 2) == 0 && 
            token->_length - 2 == strlen(data_types[i]._valka_ir)) {
            return data_types[i];
        }
    }
    return (data_types_t) {0};
}

/**
 * @brief Get the highest data type between 2.
 *
 * @param d1            data type 1
 * @param d2            data type 2
 *
 * @return The highest data type.
 */
data_types_t
get_highest_data_type(data_types_t d1, data_types_t d2)
{
    if (d1._bits_sz >= d2._bits_sz)
        return d1;
    return d2;
}
