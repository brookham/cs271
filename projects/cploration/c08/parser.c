/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Brook Hamilton
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */

char *strip(char *s){	
	

	int i = 0;
	
	char s_new[strlen(s) + 1];
	
	for (char *s2 = s; *s2; s2++) { 
	
		if (*s2 == '/' && *(s2+1)== '/'){
			break;
		}
		else if (!isspace(*s2)){
			s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
	strcpy(s, s_new);
	
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	char line[MAX_LINE_LENGTH] = {0};
	char label[MAX_LABEL_LENGTH];
	
	unsigned int line_num = 0;
	
	unsigned int instr_num = 0;

	char inst_type = 0;
	
	while (fgets(line, sizeof(line), file)) {
		line_num++;
		strip(line);
		if (instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		if (!*line){
			continue;
		}
	
		else if (is_Atype(line)){
			inst_type = 'A';
		}
		
		else if (is_label(line)){
			extract_label(line, label);
			strcpy(line, label);
			if (isalpha(line[0]) == 0){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			if (symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			symtable_insert(line, instr_num);
			inst_type = 'L';
			continue;	
		}
		
		else if (is_Ctype(line)){
			inst_type = 'C';
		}

		printf("%u: %c  %s\n", instr_num, inst_type, line);
		//printf("%c  ", inst_type);
		//printf("%s\n", line);
		instr_num++;
	}
	
}

bool is_Atype(const char *line){
	if (line[0] == '@'){
		return true;
	}
	else{
		return false;
		
}
}

bool is_label(const char *line){
	if (line[0] == '(' &&  line[strlen(line)-1]){
		return true;
	}
	else{
		return false;
	}
}

bool is_Ctype(const char *line){
	if (is_label(line) && is_Atype(line) == true){
		return false;
	}
	else{
		return true;
		
}
}
char *extract_label(const char *line, char *label){
	
	for (int i = 0; i < strlen(line); i ++){

		label[i] = line[i+1];
		
	}

	label[strlen(line) - 2] = '\0';
    return label;	
	
}