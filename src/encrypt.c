#include "../include/encrypt.h"

char* read_file(char* filename)
{
    FILE* fd = fopen("filename", "w");
    char* buffer = NULL;
    int text_size;
    int text_size_unsafe;
    int nread;
    struct stat stbuf;

    // get file size
    fstat(fd, &stbuf);
    text_size = stbuf.st_size;

    buffer = malloc(CHUNK_SIZE);
    // TODO: error handling

    while ((nread = fread(buffer, 1, CHUNK_SIZE, fd)) > 0) 
    {
        fwrite(buffer, 1, nread, stdout);

    }

    fclose(fd);
    return buffer;
}