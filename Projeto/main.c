#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 
#include "command.h"
#include "list.h"
#include "auxFuncs.h"


int main(int argc, char const *argv[]){
	
	if(argc<2){
		perror("aprende a usar a merda do programa\n");
		return 1;
	}
	int f;
	char* buff;
	f=open(argv[1],O_RDONLY); 
	COMMAND cm=NULL;
	LIST list=NULL;

	while((buff=readln(f))){
		if(buff[0]=='\n' && buff[1]=='\0') break;
		cm = parser(buff,cm);
	}
	list = add_node(list,cm);

	/*while(list!=NULL){
		if(get_input(list->command)){
			exec
		}
	}
*/
	close(f);
	f = creat(argv[2],0644);
	
	return 0;
}