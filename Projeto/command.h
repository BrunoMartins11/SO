#ifndef __COMMAND_H__
#define __COMMAND_H__

typedef struct command* COMMAND;
struct command{
	int reference;
	char* input;
	char* output;
	char* comment;
};
COMMAND make_command(int ref, char* input, char* output, char* comment);
char* get_input(COMMAND cm);
char* get_output(COMMAND cm);
char* get_comment(COMMAND cm);
int get_reference(COMMAND cm);
void set_command_input(COMMAND cm, char* input);
void set_command_output(COMMAND cm, char* output);
void set_command_comment(COMMAND cm, char* comment);
void free_command(COMMAND cm);

#endif
