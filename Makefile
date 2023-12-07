all:
	gcc word.c -o word
	gcc date.c -o date
	gcc dir.c -o dir
	gcc source.c -o source
	./source

clean:
	rm -f word date dir source