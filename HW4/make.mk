CC = gcc
CFLAGS = -Wall -Werror

EXECS = job_scheduler

all: $(EXECS)

job_scheduler: job_scheduler.o
	$(CC) $(CFLAGS) -o $@ $^

job_scheduler.o: job_scheduler.c
	$(CC) $(CFLAGS) -c -o $@ $^

debug: job_scheduler
	gdb ./job_scheduler

clean:
	rm -f *.o $(EXECS)
