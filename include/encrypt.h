#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHUNK_SIZE 1024

char* read_from_file(char* filename);

/** 
 * returns total file size in bytes.
*/
int calculate_file_size(char* filename);

