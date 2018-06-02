#include "command.h"
#include "list.h"

COMMAND parser(char* buff);
char* readln(int fildes);
char * str_dup (const char *s);
void write_file(LIST list, int fd);
char** strdivide(char*);
void exec_command(char** token, int* pi, int*po);
char* get_pos_command_out(LIST l, int pos);