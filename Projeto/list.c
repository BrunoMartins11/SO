struct list{
	COMMAND command;
	*next;
};

LIST add_node(LIST list, COMMAND cm){
	
	if(!list) list = malloc(sizeof(struct list));
	LIST head = list;
	
	while(list)
		list = list->next;
	list = cm;
	list->next = NULL;

	return head;
}

void free_list(LIST list){
	
	while(list){
		free(list);
		list=list->next;
	}
}
