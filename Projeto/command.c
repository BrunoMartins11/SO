#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "command.h"
#include "auxFuncs.h"



COMMAND make_command(char* input, char* output, char* comment){

	COMMAND cm;
	if ((cm = malloc(sizeof(struct command))) == NULL){
		perror("Memory allocation failed");
		_exit(-1);
	}
	
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
	if(!(cm->input)) 
		cm->input = str_dup(input);
	
	else{
		
		if ((cm->input= realloc(cm->input,sizeof(char)*(strlen(cm->input)+strlen(input)))) == NULL){
			perror("Memory reallocation failed");
			_exit(-1);
		}

		cm->input=  strcat(cm->input,str_dup(input));
	}
}

void set_command_output(COMMAND cm, char* output){
	if(!cm->output)
		cm->output= str_dup(output);
	
	else{
		
		if ((cm->output = realloc(cm->output, sizeof(char)*(strlen(cm->output)+strlen(output)))) == NULL){
			perror("Memory reallocation failed");
			_exit(-1);
		}

		strcat(cm->output, output);
	}
}

void set_command_comment(COMMAND cm, char* comment){
	if(!(cm->comment)) 
		cm->comment = str_dup(comment);
	
	else{
		
		if ((cm->comment = realloc(cm->comment,sizeof(char)*(strlen(cm->comment)+strlen(comment)))) == NULL){
			perror("Memory reallocation failed");
			_exit(-1);
		}

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