all: a2

CC = gcc

a2: SORT.o
	$(CC) -o a2 SORT.o

SORT.o: SORT.c
	$(CC) -c SORT.c semun.h shm_com.h

clean:
	-rm SORT.o