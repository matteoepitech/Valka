/*
** VALKA PROJECT, 2025
** src/main
** File description:
** Valka main file
*/

#include "valka.h"

/**
 * @brief Main function for valka binary.
 *
 * @param argc          ARGC
 * @param argv[]        ARGV
 *
 * @return Return status.
 */
int
main(UNUSED int argc, UNUSED char *argv[])
{
    UNUSED char *hello = MALLOC(sizeof(char) * 10);

    return cleanup_mem(OK_OUTPUT);
}
