#include "command.h"
#include "list.h"

COMMAND parser(char* buff, COMMAND cm);
char* readln(int fildes);
char * str_dup (const char *s);