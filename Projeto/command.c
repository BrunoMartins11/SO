#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "auxFuncs.h"



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
	if(!(cm->input)) cm->input = str_dup(input);
	else{
		cm->input= realloc(cm->input,sizeof(char)*(strlen(cm->input)+strlen(input)));
		cm->input=  strcat(cm->input,str_dup(input));
	}
}

void set_command_output(COMMAND cm, char* output){
	if(!cm->output)
		cm->output= str_dup(output);
	else{
		cm->output = realloc(cm->output, sizeof(char)*(strlen(cm->output)+strlen(output)));
		strcat(cm->output, output);
	}
}

void set_command_comment(COMMAND cm, char* comment){
	if(!(cm->comment)) cm->comment = str_dup(comment);
	else{
		cm->comment = realloc(cm->comment,sizeof(char)*(strlen(cm->comment)+strlen(comment)));
		cm->comment=  strcat(cm->comment,str_dup(comment));
	}
}

void free_command(COMMAND cm){
	if(cm){
	if(cm->input)
	free(cm->input);
	if(cm->output)
	free(cm->output);
	if(cm->comment)
	free(cm->comment);
	free(cm);
	}
}