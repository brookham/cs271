#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum exitcode{
/*
 * Error code 1 represents that given file does not exist.
 */
    EXIT_INCORRECT_ARGUMENTS = 1,
    EXIT_CANNOT_OPEN_FILE,
    EXIT_TOO_MANY_INSTRUCTIONS,
    EXIT_INVALID_LABEL,
    EXIT_SYMBOL_ALREADY_EXISTS,
    EXIT_INVALID_A_INSTR,
    EXIT_DEST_INVALID,
    EXIT_COMP_INVALID,
    EXIT_JMP_INVALID

    
} exitcode;

void exit_program(enum exitcode code, ...);

#endif
