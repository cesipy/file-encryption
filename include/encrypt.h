#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "../include/logger.h"

#define CHUNK_SIZE 1024
#define LOG_FILE   "logs/log.txt"

char* read_from_file(char* filename);
void write_to_file(char* filename, char* text_to_write);

/** 
 * returns total file size in bytes.
*/
int calculate_file_size(char* filename);

