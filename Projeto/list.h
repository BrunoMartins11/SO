#ifndef __LIST_H__
#define __LIST_H__
#include "command.h"
typedef struct list* LIST;
struct list{
	COMMAND command;
	LIST next;
};

LIST add_node(LIST list, COMMAND cm);
void free_list(LIST list);
COMMAND get_command(LIST l);
int list_size(LIST l);
#endif
