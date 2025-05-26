/*
** VALKA PROJECT, 2025
** src/utils/data/data_helper
** File description:
** Data helper functions
*/

#include "valka.h"

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
