

COMMAND parser(char* buff, COMMAND cm){

	for(int i=0; buff; i++){
		if(buff[i] == '$' ){
			if(!cm)
				cm = make_command(buff,NULL,NULL);
				break;
				else{ 
					set_command_input(cm,buff); 
					break;
					}
		}
		if(buff[i]!=' ' && buff[i]!='$' && buff[i]!='>>>'){
		    if(!cm)
				cm = make_command(NULL,NULL,buff);
				break;
				else{ 
					set_command_comment(cm,buff); 
					break;
					}	
		}
		if(buff[i]=='>>>'){
		    if(!cm)
				cm = make_command(NULL,buff,NULL);
				break;
				else{ 
					set_command_output(cm,buff); 
					break;
					}
	}
	return cm;
}