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

int parse(FILE * file, instruction *instructions){
	char line[MAX_LINE_LENGTH] = {0};
	char label[MAX_LABEL_LENGTH];
	char tmp_line[MAX_LINE_LENGTH];
	unsigned int line_num = 0;
	
	unsigned int instr_num = 0;

	char inst_type = 0;
	
	add_predefined_symbols();

	instruction instr;
	while (fgets(line, sizeof(line), file)) {
		line_num++;
		strip(line);
		strcpy(tmp_line, line);
		if (instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		if (!*line){
			continue;
		}
		if (is_label(line)){
			inst_type = 'L';
			extract_label(line, label);
			strcpy(line, label);
			if (isalpha(line[0]) == 0){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			if (symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			symtable_insert(line, instr_num);
		}
		else if (is_Atype(line)){
			inst_type = 'A';
			if (!parse_A_instruction(line, &instr.inst.a)){
    			exit_program(EXIT_INVALID_A_INSTR, line_num, line);
 			}
			if (instr.inst.a.is_addr == false){
				printf("A: %s\n", instr.inst.a.operand.label);
			}else{
				printf("A: %d\n", instr.inst.a.operand.address);
			}
		}
		else if (is_Ctype(line)){
			inst_type = 'C';
			parse_C_instruction(tmp_line, &instr.inst.c);
			if (instr.inst.c.dest == DEST_INVALID){
				exit_program(EXIT_DEST_INVALID, line_num, line);
			}
			if (instr.inst.c.comp == COMP_INVALID){
				exit_program(EXIT_COMP_INVALID, line_num, line);
			}
			if(instr.inst.c.jump == JMP_INVALID){
				exit_program(EXIT_JMP_INVALID, line_num, line);
			}
			printf("C: d=%d, c=%d, j=%d\n", instr.inst.c.dest, instr.inst.c.comp, instr.inst.c.jump);
		}
		//printf("%u: %c  %s\n", instr_num, inst_type, line);
		//printf("%c  ", inst_type);
		//printf("%s\n", line);
		instr.type = inst_type;
		instructions[instr_num++] = instr;

	}
	return instr_num;
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
	if (line[0] == '(' &&  line[strlen(line)-1] == ')'){
		return true;
	}
	else{
		return false;
	}
}

bool is_Ctype(const char *line){
	if (!is_Atype(line) && !is_label(line)){
		return true;
	}
	else{
		return false;
		
}
}
char *extract_label(const char *line, char *label){
	
	for (int i = 0; i < strlen(line); i ++){

		label[i] = line[i+1];
		
	}

	label[strlen(line) - 2] = '\0';
    return label;	
	
}
void add_predefined_symbols(){

    for (int i=0; i < NUM_PREDEFINED_SYMBOLS; i++){

        struct predefined_symbol predefined_symbol = predefined_symbols[i];
		symtable_insert(predefined_symbol.name, predefined_symbol.addr);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr){
    char *s = malloc(strlen(line) + 1);
    strcpy(s, line + 1);
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if (s == s_end){
        instr->operand.label = (char *)malloc(strlen(line) + 1);
        strcpy(instr->operand.label, s);
		instr->is_addr = false;
    }
	else if (*s_end != 0){
		return false;
	}
	else{
		instr->operand.address = result;
		instr->is_addr = true;
	}

	return true;
}

void parse_C_instruction(char *line, c_instruction *instr){
	char *temp;
	char *dest, *comp, *jump;

	int *a = malloc(sizeof(int));

	temp = strtok(line, ";");
	jump = strtok(NULL, ";");

	dest = strtok(temp, "=");
	comp = strtok(NULL, "=");
	if (comp == NULL){
		comp = dest;
		dest = NULL;
	}

	if (strstr(comp, "M") != NULL){
		*a = 1;
	}
	else{
		*a = 0;
	}
	instr->a = *a;
	instr->jump = str_to_jumpid(jump);
	instr->comp = str_to_compid(comp, a);
	instr->dest = str_to_destid(dest);

}
