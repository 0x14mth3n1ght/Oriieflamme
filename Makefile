CC = gcc -Wall -Wextra -std=c99

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SRC := $(wildcard $(SRCDIR)/*.c)
HEADER := $(wildcard $(SRCDIR)/*.h)
OBJDIR  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

jeu: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -rf *.o

rmall: clean
	rm -rf jeu

main.o: carte.o faction.o interface.o plateau.o
carte.o: carte.h
faction.o: faction.h
interface.o: interface.h
plateau.o: plateau.h
