all: src/main.c src/encrypt.c src/logger.c src/io_handling.c
	gcc src/encrypt.c src/main.c src/logger.c src/io_handling.c -o main

# for testing, currently not in use

clean:
	rm -f src/a.out main
