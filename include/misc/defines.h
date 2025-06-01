/*
** VALKA PROJECT, 2025
** include/misc/defines
** File description:
** Valka defines header file
*/


#ifndef _VALKA_DEFINES_H_
    #define _VALKA_DEFINES_H_


    #ifndef TRUE
        #define TRUE 1
    #endif /* ifndef TRUE */
    
    #ifndef FALSE
        #define FALSE 0
    #endif /* ifndef FALSE */



    #ifndef OK_OUTPUT
        #define OK_OUTPUT 0
    #endif /* ifndef OK_OUTPUT */
    
    #ifndef KO_OUTPUT
        #define KO_OUTPUT 1
    #endif /* ifndef KO_OUTPUT */



    #ifndef UNUSED
        #define UNUSED __attribute__((unused))
    #endif /* ifndef UNUSED */


    #define COLOR_RESET   "\033[0m"
    #define COLOR_BLUE    "\033[34m"
    #define COLOR_GREEN   "\033[32m"
    #define COLOR_RED   "\033[31m"
    #define COLOR_YELLOW  "\033[33m"
    #define COLOR_CYAN    "\033[36m"
   
    #define MAX_INDICES_DEPTH 16 // var[0][0][0]...16x
    #define OPERATORS_STR "/+-*%"
    #define SYSCALL_BUILTIN_NAME "syscall"
    #define START_ENTRY_POINT "main"

    /* All data types in Valka */
    #define T_I32 1
    #define T_BOOL 2
    #define T_CHAR 3
    #define T_VOID 4
    #define T_VARG 5
    #define T_FLOAT 6

    /* All condition operators in Valka */
    #define OP_EQUAL 1
    #define OP_GREATER_EQ 2
    #define OP_LOWER_EQ 3
    #define OP_GREATER 4
    #define OP_LOWER 5
    #define OP_NOT_EQUAL 6
    
    /* Types for identifier AST, var, func, return, if, for, while, .. */
    #define IDENTIFIER_ID_VAR 1
    #define IDENTIFIER_ID_FUNC 2
    #define IDENTIFIER_ID_RETURN 3
    #define IDENTIFIER_ID_IF 4
    #define IDENTIFIER_ID_FOR 5
    #define IDENTIFIER_ID_WHILE 6


#endif /* ifndef _VALKA_DEFINES_H_ */
