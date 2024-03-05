CC = gcc
CFLAGS = -Wall -Werror

EXECS = search

all: $(EXECS)

search: search.o
	$(CC) $(CFLAGS) -o $@ $^

search.o: search.c
	$(CC) $(CFLAGS) -c -o $@ $^

debug: search
	gdb ./search

clean:
	rm -f *.o $(EXECS)
