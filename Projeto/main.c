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
	
	int f;
	int pdi[2];
	int pdo[2];
	char* buff;

	if(argc!=2){
		perror("Missing notebook file.\n");
		return -1;
	}
	
	if ((f=open(argv[1],O_RDONLY)) == -1){
		perror("Error opening file\n");
		exit(-1);
	}

	COMMAND cm=NULL;
	LIST list=NULL;

	while((buff=readln(f))){
		
		if(strcmp(">>>\n",buff)==0){
			do{
				 free(buff);
				 buff=readln(f);
			}
			while(strcmp("<<<\n",buff));
		}
		
		else{
			
			if(buff[0]=='\n' && buff[1]=='\0') 
				break;
			
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
		int j;
		
		if(list->command->input){
			if (pipe(pdi) == -1){
				perror("Pipe failed\n");
				_exit(-1);
			}

			if (pipe(pdo) == -1){
				perror("Pipe failed\n");
				_exit(-1);
			}

			if ((j = fork()) == -1){
				perror("Error creating new proccess\n");
				_exit(-1);
			}

			token = strdivide(list->command->input);
			
			if(j==0 && isFirst){
				close(pdi[0]);
				close(pdi[1]);
				exec_command(token,NULL,pdo);
			}
			
			else if(j==0){
				exec_command(token,pdi,pdo);	
			}

			close(pdo[1]);
			close(pdi[0]);
			int n=1;
			
			if(!isFirst){
				if (write(pdi[1], out, strlen(out)) == -1){
					perror("Writing error\n");
					_exit(-1);
				}
			}

			close(pdi[1]);
			
			while(n != 0){
				char buffer[1024];
				
				if ((n=read(pdo[0], buffer, 1023)) == -1){
					perror("Error reading from file\n");
					_exit(-1);
				}

				buffer[n] = 0;
				
				if(n==0) 
					break;
				
				set_command_output(list->command,buffer);
			}
			wait(NULL);
			isFirst=0;
			out = list->command->output;
		}
		list = list->next;
	}

	close(f);
	
	if ((f = creat(argv[1],0644)) == -1){
		perror("Error creating file\n");
		_exit(-1);
	}
	
	write_file(fim,f);
	close(f);
	free_list(fim);
	free(buff);
	return 0;
}
