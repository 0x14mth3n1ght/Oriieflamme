CC = gcc -Wall -Wextra -std=c99

jeu: main.o
	$(CC) obj/*.o -o bin/jeu

clean:
	rm -rf obj/*.o

rmall: clean
	rm -rf bin/jeu

main.o: carte.o faction.o interface.o plateau.o structure.o
	$(CC) -c src/main.c -o  obj/main.o

carte.o: header/carte.h
	$(CC) -c src/carte.c -o obj/carte.o

faction.o: header/faction.h
	$(CC) -c src/faction.c -o obj/faction.o

interface.o: header/interface.h
	$(CC) -c src/interface.c -o obj/interface.o

plateau.o: header/plateau.h
	$(CC) -c src/plateau.c -o obj/plateau.o

structure.o: header/structure.h 
	$(CC) -c src/structure.c -o obj/structure.o
