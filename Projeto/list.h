#ifndef __LIST_H__
#define __LIST_H__
#include "command.h"
typedef struct list* LIST;

LIST add_node(LIST list, COMMAND cm);
void free_list(LIST list);

#endif
