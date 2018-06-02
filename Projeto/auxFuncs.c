#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "auxFuncs.h"
#include "list.h"
#include "command.h"

char *readln(int fildes)
{
    char *buf;
    int size = 10;
    int load = 0;
    char c;
    int r = 0;

    if ((buf = malloc(sizeof(char) * 10)) == NULL){
        perror("Memory allocation failed\n");
        _exit(-1);
    }

    while ((r = read(fildes, &c, 1)) > 0){
        if (c == '\n')
            break;

        if (load >= (size - 2)){ //-2 pq e para ter espaço para o \0 e \n
            size *= 2;
            if ((buf = realloc(buf, sizeof(char) * size)) == NULL){
                perror("Memory reallocation failed\n");
                _exit(-1);
            }
        }
        buf[load++] = c;
    }

    buf[load++] = '\n';
    buf[load] = '\0';

    return buf;
}

COMMAND parser(char *buff){
    COMMAND cm = NULL;

    if (buff[0] == '$')
        cm = make_command(buff, NULL, NULL);

    if (buff[0] != '$' && strcmp(buff, ">>>"))
        cm = make_command(NULL, NULL, buff);

    return cm;
}

char *str_dup(const char *s){
    if (s == NULL)
        return NULL;

    char *d = malloc(strlen(s) + 1);
    if (d == NULL)
        return NULL;

    strcpy(d, s);

    return d;
}

void write_file(LIST list, int fd){
    COMMAND cm;

    while (list){
        cm = get_command(list);
        
        if (get_comment(cm))
            if (write(fd, get_comment(cm), strlen(get_comment(cm))) == -1){
                perror("Writing error\n");
                _exit(-1);
            }

        if (get_input(cm))
            if (write(fd, get_input(cm), strlen(get_input(cm))) == -1){
                perror("Writing error\n");
                _exit(-1);
            }

        if (get_output(cm)){

            if (write(fd, ">>>\n", 4) == -1){
                perror("Error writing on file\n");
                _exit(-1);
            }

            if (write(fd, get_output(cm), strlen(get_output(cm))) == -1){
                perror("Error writing on file\n");
                _exit(-1);
            }

            if (write(fd, "<<<\n", 4) == -1){
                perror("Error writing on file\n");
                _exit(-1);
            }
        }
        list = list->next;
    }
}

char **strdivide(char *str){
    char *s = str_dup(str);
    int n;
    char **res = NULL;
    char *p;
    n = 0;
    p = strtok(s, " ");
    while(p){

        if ((res = realloc(res, sizeof(char *) * (n + 1))) == NULL){
            perror("Memory reallocation failed\n");
            _exit(-1);
        }

        res[n++] = str_dup(p);
        p = strtok(NULL, " ");
    }

    res[n- 1] = strtok(res[n - 1], "\n");
    
    if ((res = realloc(res, sizeof(char *) * (n + 1))) == NULL){
        perror("Memory reallocation failed\n");
        _exit(-1);
    }

    res[n] = 0;
    return res;
}

void exec_command(char **token, int *ppi, int *ppo){

    if (ppi != NULL){
        dup2(ppi[0], 0);
        close(ppi[0]);
        close(ppi[1]);
    }

    dup2(ppo[1], 1);
    close(ppo[1]);
    close(ppo[0]);

    if (execvp(token[1], token + 1) == -1){
        perror("Error executing command\n");
        _exit(-1);
    }

    _exit(1);
}
