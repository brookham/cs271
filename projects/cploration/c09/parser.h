/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Brook Hamilton
 * [TERM] FALL 2024
 * 
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "hack.h"

#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH  MAX_LINE_LENGTH - 2

/** function prototypes **/
void add_predefined_symbols();

typedef int16_t hack_addr;

typedef int16_t opcode;

char *extract_label(const char *line, char* label);

char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);

typedef enum{
    INVALID = -1,
    ATYPE,
    CTYPE
}instr_type;


typedef struct c_instruction{

    opcode a:1;
    opcode comp:7;
    opcode dest:3;
    opcode jump:3;

} c_instruction;

typedef struct a_instruction{
    union{
        hack_addr address;
        char *label;
    }operand;
    bool is_addr;

} a_instruction;

typedef struct instruction{
    union inst{
        a_instruction a;
        c_instruction c;
    }inst;
    instr_type type;
} instruction;

bool parse_A_instruction(const char *line, a_instruction *instr);

#endif