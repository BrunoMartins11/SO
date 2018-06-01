#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "command.h"
#include "list.h"




LIST add_node(LIST list, COMMAND cm){
	if(!list){
		
		if ((list = malloc(sizeof(struct list))) == NULL){
			perror("Memory allocation failed");
			_exit(-1);

		}

		list->command = cm;
		list->next = NULL;
		return list;
	}
	
	LIST head = list;
	
	while(list->next)
		list = list->next;
	
	if ((list->next = malloc(sizeof(struct list))) == NULL){
		perror("Memory allocation failed");
		_exit(-1);
	}

	(list->next)->command = cm;
	(list->next)->next = NULL;

	return head;
}

COMMAND get_command(LIST l){
	return l->command;
}

void free_list(LIST list){
	
	while(list){
		free_command(list->command);
		LIST fr=list;
		list=list->next;
		free(fr);
		
	}
}
