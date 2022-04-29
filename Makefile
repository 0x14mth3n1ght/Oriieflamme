CC = gcc -Wall -Wextra -std=c99

jeu: main.o
	gcc obj/main.o -o bin/jeu

clean:
	rm -rf obj/*.o

rmall: clean
	rm -rf bin/jeu

main.o: carte.o faction.o interface.o plateau.o structure.o
	gcc -c src/main.c -o  obj/main.o

carte.o: header/carte.h
	gcc -c src/carte.c -o obj/carte.o

faction.o: header/faction.h
	gcc -c src/faction.c -o obj/faction.o

interface.o: header/interface.h
	gcc -c src/interface.c -o obj/interface.o

plateau.o: header/plateau.h
	gcc -c src/plateau.c -o obj/plateau.o

structure.o: header/structure.h 
	gcc -c src/structure.c -o obj/structure.o
