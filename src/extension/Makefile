OBJS	= main.o
CC	 = gcc
FLAGS	 = -g -c -Wall -D_DEFAULT_SOURCE  -std=c99 -pedantic -O3 -DNDEBUG

main: main.o

main.o: main.c structures.h
	$(CC) $(FLAGS) main.c -o main.o

clean:
	rm -f $(OBJS) $(OUT)