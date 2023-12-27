all:
	gcc src/word.c -o word -lncurses
	gcc src/date.c -o date -lncurses
	gcc src/dir.c -o dir -lncurses
	gcc src/vikshell.c -o vikshell -lncurses
	./vikshell

clean:
	rm -f word date dir vikshell