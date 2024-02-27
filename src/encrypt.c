#include "../include/encrypt.h"

char* read_from_file(char* filename)
{
    FILE* fd;
    char* buffer = NULL;
    int text_size;
    int text_size_unsafe;
    int nread;
    struct stat stbuf;

    fd = fopen(filename, "r");
    if (fd == NULL) 
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }


    buffer = malloc(CHUNK_SIZE);
    if (buffer == NULL) 
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    while ((nread = fread(buffer, 1, CHUNK_SIZE, fd)) > 0) 
    {
        fwrite(buffer, 1, nread, stdout);
        if(ferror(fd))
        {
            fprintf(stderr, "error while reading file");
            exit(EXIT_FAILURE);
        }
    }

    if (fclose(fd) != 0) 
    {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
    }
    return buffer;
}