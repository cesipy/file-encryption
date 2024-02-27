#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CHUNK_SIZE 1024

char* read_from_file(char* filename);

