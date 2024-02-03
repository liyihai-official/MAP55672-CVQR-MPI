CC = gcc

CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -llapack -lopenblas -lblas -lmpi


all: test

load.o: load.c load.h
	$(CC) $(CFLAGS) -c $< -o $@

test: test.c load.o
	$(CC) -g $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o test
