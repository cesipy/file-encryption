#include "../include/encrypt.h"

char* read_from_file(char* filename)
{
    FILE* file;
    char* buffer = NULL;
    int file_size;
    int text_size_unsafe;
    int nread;
    struct stat stbuf;

    file_size = calculate_file_size(filename);

    file = fopen(filename, "r");
    if (file == NULL) 
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

    while ((nread = fread(buffer, 1, CHUNK_SIZE, file)) > 0) 
    {
        fwrite(buffer, 1, nread, stdout);
        if(ferror(file))
        {
            fprintf(stderr, "error while reading file");
            exit(EXIT_FAILURE);
        }
    }

    if (fclose(file) != 0) 
    {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
    }
    return buffer;      // do not return buffer, but 
}


int calculate_file_size(char* filename)
{
    int fd, file_size;
    struct stat stbuf;

    fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        // todo: handle error
        perror("calculating file size");
    }

    if ((fstat(fd, &stbuf) != 0) || (!S_ISREG(stbuf.st_mode))) 
    {
        perror("error fstat");
    }

    file_size = stbuf.st_size;
    // todo: logging of file size
    
    close(fd);
    // todo: error handling

    return file_size;
}