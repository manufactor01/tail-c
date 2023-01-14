CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --show-reachable=yes --track-origins=yes
EXEC = pruebas
OBJFILE = tail.o cola.o
TEXTFILE = archivo.txt
N = 3
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
$(EXEC): $(OBJFILE)
	$(CC) $(CFLAGS) $(OBJFILE) -o $(EXEC)
all: clear $(EXEC)

clear:
	clear
free: $(EXEC) $(OBJFILE)
	rm -f $(EXEC) *.o
valgrind: all
	valgrind $(VFLAGS) ./$(EXEC) $(N) < $(TEXTFILE)