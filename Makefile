all:
	gcc word.c -o word -lncurses
	gcc date.c -o date -lncurses
	gcc dir.c -o dir -lncurses
	gcc source.c -o source -lncurses
	./source

clean:
	rm -f word date dir source