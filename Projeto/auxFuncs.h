#include "command.h"
#include "list.h"

COMMAND parser(char* buff);
char* readln(int fildes);
char * str_dup (const char *s);
void write_file(LIST list, int fd);