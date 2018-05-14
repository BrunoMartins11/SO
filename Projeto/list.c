#include <stdlib.h>
#include "command.h"
#include "list.h"


struct list{
	COMMAND command;
	LIST next;
};

LIST add_node(LIST list, COMMAND cm){
	
	if(!list){
		list = malloc(sizeof(struct list));
		list->command = cm;
		list->next = NULL;
		return list;
	}
	LIST head = list;
	
	while(list->next)
		list = list->next;
	list->next = malloc(sizeof(struct list));
	(list->next)->command = cm;
	(list->next)->next = NULL;

	return head;
}

void free_list(LIST list){
	
	while(list){
		free(list);
		list=list->next;
	}
}
