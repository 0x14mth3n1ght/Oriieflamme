CC=gcc -Wall -Wextra -std=c99

jeu: main.o carte.o faction.o interface.o plateau.o
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