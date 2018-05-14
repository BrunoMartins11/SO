#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h>
#include <string.h>
#include "auxFuncs.h"
#include "list.h"
#include "command.h"

char* readln(int fildes){
        
        char* buf = malloc(sizeof(char)*10);
        int size = 10;
        int load = 0;
        char c;
        int r=0;
        
      	while((r = read(fildes, &c, 1)) > 0  ){
          if(c=='\n') break;
          if(load>=(size-2)) {//-2 pq e para ter espaço para o \0 e \n
            size*=2;
            buf = realloc(buf,sizeof(char)*size);
          }
          buf[load++]=c;
			  }
        buf[load++]='\n';
        buf[load] = '\0';
       return buf;
}

COMMAND parser(char* buff, COMMAND cm){ 

    if(buff[0] == '$' ){
      if(!cm)
        cm = make_command(buff,NULL,NULL);
        else{ 
          set_command_input(cm,buff); 
          }
    }
    if(buff[0]!='$' && strcmp(buff,">>>")){
        if(!cm)
        cm = make_command(NULL,NULL,buff);
        else{ 
          set_command_comment(cm,buff); 
          } 
    }
    
  return cm;
}



char* str_dup (const char *s) {
    if(s == NULL) return NULL;          
    char *d = malloc (strlen (s) + 1); 
    if (d == NULL) return NULL;       
    strcpy (d,s);                    
    return d;                       
}