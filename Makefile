all: src/main.c src/encrypt.c
	gcc src/encrypt.c src/main.c -o main

# for testing, currently not in use

clean:
	rm -f src/a.out main
