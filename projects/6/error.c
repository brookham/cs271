#include "error.h"

const char *error_message[] = 
{
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than th emaximum of %u instructions.",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
    [EXIT_INVALID_A_INSTR] = "Line %u: %s : Invalid A-instruction operand",
    [EXIT_DEST_INVALID] = "Line %u: %s : Invalid destination part of C-instruction",
    [EXIT_COMP_INVALID] = "Line %u: %s : Invalid compare part of C-instruction",
    [EXIT_JMP_INVALID] = "Line %u: %s : Invalid jump part of C-instruction"
};

void exit_program(enum exitcode code, ...)
{
    va_list arguments;
    va_start(arguments, code);

    printf("ERROR: ");
    vprintf(error_message[code], arguments);
    printf("\n");

    va_end(arguments);
    exit(code);
}