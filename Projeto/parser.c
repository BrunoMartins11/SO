

COMMAND parser(char* buff, COMMAND cm){

		if(buff[i] == '$' ){
			if(!cm)
				cm = make_command(buff,NULL,NULL);
				else{ 
					set_command_input(cm,buff); 
					}
		}
		if(buff[i]!='$' && strncmp(buff,">>>",3)){
		    if(!cm)
				cm = make_command(NULL,NULL,buff);
				else{ 
					set_command_comment(cm,buff); 
					}	
		}
		if(strncmp(buff,">>>",3)){
		    if(!cm)
				cm = make_command(NULL,buff,NULL);
				else{ 
					set_command_output(cm,buff);
					}
	return cm;
}