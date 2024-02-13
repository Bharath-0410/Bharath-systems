# This is the make file for the HW2 bnakka_HW02.c
CC = gcc
EXECS = bnakka_HW02

build : $(EXECS)

%.o : %.c
	$(CC) -c -o $@ $^

debug :	$(EXECS)
	gdb ./$(EXECS) -tui

clean : 
	rm *.o $(EXECS)
