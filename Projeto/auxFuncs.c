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

COMMAND parser(char* buff){
  COMMAND cm=NULL; 
    if(buff[0] == '$' )
        cm = make_command(buff,NULL,NULL);
    if(buff[0]!='$' && strcmp(buff,">>>"))
        cm = make_command(NULL,NULL,buff);
    
  return cm;
}



char* str_dup (const char *s) {
    if(s == NULL) return NULL;          
    char *d = malloc (strlen (s) + 1); 
    if (d == NULL) return NULL;       
    strcpy (d,s);                    
    return d;                       
}

void write_file(LIST list, int fd){

  COMMAND cm;
  
  while(list){
    cm = get_command(list);
    if(get_comment(cm)) write(fd,get_comment(cm),strlen(get_comment(cm)));
    if(get_input(cm)) write(fd,get_input(cm),strlen(get_input(cm)));
    if(get_output(cm)){
     write(fd,">>>\n",4);
     write(fd,get_output(cm),strlen(get_output(cm)));
     write(fd,"<<<\n",4);
    }
    list=list->next;
  }  
}

char** strdivide(char* str){

  char* s = str_dup(str);
  int n_spaces;
  char** res = NULL;

  n_spaces = 0;
  for(char * p = strtok (s, " "); p; p = strtok (NULL, " ")) {
    res = realloc (res, sizeof (char*) * (n_spaces+1));
    res[n_spaces++] = p;
  }
  res[n_spaces-1] = strtok (res[n_spaces-1], "\n");
  res = realloc (res, sizeof (char*) * (n_spaces+1));
  res[n_spaces] = 0;
return res;
}

void exec_command(char** token, int* ppi, int* ppo){

    if(ppi!=NULL){
        dup2(ppi[0],0);
        close(ppi[0]);
        close(ppi[1]);
    }
    dup2(ppo[1],1);
    close(ppo[1]);
    close(ppo[0]);
    execvp(token[1],token+1);
    _exit(1);
}

