/*
** VALKA PROJECT, 2025
** src/utils/definitions/definitions_helper
** File description:
** Contains functions for helping with definitions
*/

#include "valka.h"

/**
 * @brief Add one definition to the global variable containing all definitions.
 *
 * @param def   The def of the definition
 * @param val   The value of the definition
 *
 * @return OK_OUTPUT if everything worked.
 */
uint8_t
add_definition(char *def, char *val)
{
    definitions_count++;
    definitions_src = REALLOC(definitions_src,
        sizeof(definition_t) * definitions_count);
    if (def == NULL)
        definitions_src[definitions_count - 1]._def = NULL;
    else
        definitions_src[definitions_count - 1]._def = strdup_valka(def);
    if (val == NULL)
        definitions_src[definitions_count - 1]._val = NULL;
    else
        definitions_src[definitions_count - 1]._val = strdup_valka(val);
    return OK_OUTPUT;
}
