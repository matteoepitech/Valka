/*
** VALKA PROJECT, 2025
** src/utils/definitions/definitions_helper
** File description:
** Add the base functions
*/

#include "valka.h"

/**
 * @brief Create the base definitions for the base of a Valka program.
 *
 * @return OK_OUTPUT if everything worked.
 */
uint8_t
create_base_definitions(void)
{
    add_definition("false", "0");
    add_definition("true", "1");
    add_definition(NULL, NULL);
    return OK_OUTPUT;
}
