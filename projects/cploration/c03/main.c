/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Brook Hamilton
 * [TERM] Fall 2024
 * 
 ****************************************/
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define MAX_LINE_LENGTH 200
/*
										--NOTES FOR MYSELF--
*C file handling:
1. stream oriented data files: the data is stored in the smae manner as it appears on the screen.
2. system oreients data files: the data files are more closely associated with the OS

*C file opperations:
creation of a new file, opening, reading, writingdata in afile, closing a file.

*Steps for processing a file:
1. Declare a file pointer variable
2. Open a file using fopen()
3. Process the file usin th esuitable function
4. close the file using fclose() function

*fopen, fclose, getc, putc, getw, putw, fprintf, fscanf, fgets, fputs, feof
*/

//Exercise 1: Accepting arguments
int main(int argc, const char *argv[]){	

if (argc < 2){
//Exercise 2: Working with Arguments	
	printf("Usage: %s [filename]\n", argv[0]);
	exit(EXIT_FAILURE);
	}

//Exercise 3: Open the input file
FILE *fin = fopen( argv[1], "r" );{
if (fin == NULL){
	perror("Unable to open file!");
	exit(EXIT_FAILURE);
	}
}
//Exercise 4: Open the output file
char out_file[MAX_LINE_LENGTH];
//first argument(destination of where new string will be stored), second argument(gets number of
//characters in array of outfule so you don texceed capacity
//third argument(format string wich shows how to format the output)
//fourth argument( value that will %s will replace
snprintf(out_file, sizeof(out_file), "%s.echo", argv[1]);


FILE *fout = fopen(out_file, "w+" );{
	if (fout == NULL){
	perror("Unable to open file!");
	exit(EXIT_FAILURE);
}
}
//Exercise 5: Reading in the file
char line[MAX_LINE_LENGTH] = {0};
unsigned int line_num = 0;

while (fgets(line, sizeof(line), fin)) {
	line_num++;
	printf("[%04d] %s", line_num, line);
	fprintf(fout, "%s", line);
	
}
//Exercise 6: Close the file pointers
	fclose(fin);
    fclose(fout);
}