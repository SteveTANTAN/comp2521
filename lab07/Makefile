CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=tests.o Graph.o mattsGraph.o Queue.o

tests : $(OBJS)
	$(CC) -o tests $(OBJS)

tests.o : tests.c Graph.h mattsGraph.h
Graph.o : Graph.c Graph.h
mattsGraph.o : mattsGraph.c mattsGraph.h
Queue.o : Queue.c Queue.h Item.h

clean :
	rm -f tests $(OBJS) core *.dSYM
