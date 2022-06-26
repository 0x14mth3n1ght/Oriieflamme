CC = gcc -Wall -Wextra -std=c99 -g -fcommon

jeu: main.o
	$(CC) obj/*.o -o bin/jeu `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm
debug: jeu
debug: CC += -DDEBUG

clean:
	rm -rf obj/*.o

rmall: clean
	rm -rf bin/jeu

main.o: carte.o faction.o interface.o plateau.o structure.o bot.o
	$(CC) -c src/main.c -o  obj/main.o 

carte.o: header/carte.h
	$(CC) -c src/carte.c -o obj/carte.o

faction.o: header/faction.h
	$(CC) -c src/faction.c -o obj/faction.o

interface.o: header/interface.h
	$(CC) -c src/interface.c -o obj/interface.o `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

plateau.o: header/plateau.h
	$(CC) -c src/plateau.c -o obj/plateau.o

structure.o: header/structure.h 
	$(CC) -c src/structure.c -o obj/structure.o

bot.o: header/bot.h
	$(CC) -c src/bot.c -o obj/$@
