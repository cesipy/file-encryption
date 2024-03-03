# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99
LDFLAGS := -lssl -lcrypto
INCLUDES := -I/opt/homebrew/opt/openssl@3/include
LIB := -L/opt/homebrew/opt/openssl@3/lib

# Source files
SRCS := src/main.c src/encrypt.c src/logger.c src/io_handling.c
OBJS := $(SRCS:.c=.o)
EXEC := main

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(LIB) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
