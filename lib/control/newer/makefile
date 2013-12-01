CC = gcc
LFLAGS = -Wall
CFLAGS = -Wall -c
EXEC = test
OBJS = test.o

test: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o test

test.o: test.c control-v2.h
	$(CC) $(CFLAGS) test.c

clean:
	\rm *.o *~ $(EXEC)

tar:
	tar -cvf test.tar test.c control-v2.h makefile
