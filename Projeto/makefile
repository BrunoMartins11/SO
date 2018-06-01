CFLAGS=-Wall -Wextra -pedantic -O2 -g -std=c99 
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
EXEC=notebook

instalar: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
	

clean:
	rm $(EXEC) *.o
