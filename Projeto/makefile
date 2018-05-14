CFLAGS=-Wall -Wextra -pedantic -O2 -g
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
EXEC=prog

instalar: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
	

clean:
	rm $(EXEC) *.o