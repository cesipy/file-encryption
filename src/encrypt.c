#include "../include/encrypt.h"

char* read_from_file(char* filename)
{
    FILE* file;
    char* buffer = NULL;        // temporary buffer for each chunk.
    int file_size;
    int text_size_unsafe;
    int nread;
    int total_read = 0;
    struct stat stbuf;
    
    file_size = calculate_file_size(filename);
    char* result_buffer = malloc(file_size + 1);    // +1 for \0;

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

    // iterate over text
    while (1) 
    {
        nread = fread(buffer, 1, CHUNK_SIZE, file);
        
        if (nread > 0) 
        {
            memcpy(result_buffer + total_read, buffer, nread);       // copy to results
            total_read += nread;
            //fwrite(buffer, 1, nread, stdout);
            if(ferror(file))
            {
                fprintf(stderr, "error while reading file");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            break;
        }
    }

    // add termination symbol
    result_buffer[file_size] = '\0';

    if (fclose(file) != 0) 
    {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
    }

    free(buffer);

    return result_buffer;
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