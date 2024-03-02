all: src/main.c src/encrypt.c src/logger.c src/io_handling.c
	gcc src/encrypt.c src/main.c src/logger.c src/io_handling.c -o main


clean:
	rm -f src/a.out main
