#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>
#include <sys/wait.h>
#include "command.h"
#include "list.h"
#include "auxFuncs.h"


int main(int argc, char const *argv[]){
	
	if(argc<2){
		perror("aprende a usar a merda do programa\n");
		return 1;
	}
	int f;
	int pdi[2];
	int pdo[2];
	char* buff;
	f=open(argv[1],O_RDONLY); 
	COMMAND cm=NULL;
	LIST list=NULL;

	while((buff=readln(f))){
		if(strcmp(">>>\n",buff)==0){
			do{
				 free(buff);
				 buff=readln(f);
			}while(strcmp("<<<\n",buff));
		}else{
			if(buff[0]=='\n' && buff[1]=='\0') break;
			cm = parser(buff);
			list = add_node(list,cm);
		}
			free(buff);
		
	}
	LIST fim = list;
	
	int isFirst=1;	
	while(list!=NULL){
		char** token = NULL;
		char* out;
		if(list->command->input){
			pipe(pdi);
			pipe(pdo);
			int j = fork();
			token = strdivide(list->command->input);
			if(j==0 && isFirst){
				close(pdi[0]);
				close(pdi[1]);
				exec_command(token,NULL,pdo);
			}else if(j==0){
				exec_command(token,pdi,pdo);	
			}
			close(pdo[1]);
			close(pdi[0]);
			int n=1;
			if(!isFirst){
				write(pdi[1], out, strlen(out));
			}
			close(pdi[1]);
			while(n != 0){
				char buffer[1024];
				n=read(pdo[0], buffer, 1023);
				buffer[n] = 0;
				if(n==0) break;
				set_command_output(list->command,buffer);
			}
			wait(NULL);
			isFirst=0;
			out = list->command->output;
		}
		list = list->next;
	}

	close(f);
	//f = creat(argv[2],0644);
	write_file(fim,2);
	close(1);
	free_list(fim);
	free(buff);
	return 0;
}
