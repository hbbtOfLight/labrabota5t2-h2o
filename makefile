#Makefile for labrabota5

bin/app: obj/main.o obj/functional.o obj/menu.o
	gcc -o bin/app obj/main.o obj/functional.o obj/menu.o -l sqlite3

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -l sqlite3

obj/menu.o: src/menu.c
	gcc -c src/menu.c -o obj/menu.o -l sqlite3

obj/functional.o: src/functional.c
	gcc -c src/functional.c -o obj/functional.o -l sqlite3

clean:
	rm -f obj/*.o bin/task
