#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "auxFuncs.h"

struct command{
	char* input;
	char* output;
	char* comment;
};

COMMAND make_command(char* input, char* output, char* comment){
	
	COMMAND cm = malloc(sizeof(struct command));
	
	cm->input = str_dup(input);
	cm->output = str_dup(output);
	cm->comment = str_dup(comment);

	return cm;
}

char* get_input(COMMAND cm){
	return cm->input;
}

char* get_output(COMMAND cm){
	return cm->output;
}

char* get_comment(COMMAND cm){
	return cm->comment;
}

void set_command_input(COMMAND cm, char* input){
	cm->input= str_dup(input);
}

void set_command_output(COMMAND cm, char* output){
	cm->output= str_dup(output);
}

void set_command_comment(COMMAND cm, char* comment){
	if(!(cm->comment)) cm->comment = str_dup(comment);
	else{
		cm->comment = realloc(cm->comment,sizeof(char)*(strlen(cm->comment)+strlen(comment)));
		cm->comment=  strcat(cm->comment,str_dup(comment));
	}
}

void free_command(COMMAND cm){
	free(cm->input);
	free(cm->output);
	free(cm->comment);
	free(cm);
}