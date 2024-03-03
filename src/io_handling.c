#include "../include/encrypt.h"


char* read_from_file(char* filename)
{
    logger("opening file to read from");
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
            //logger("read until: %d", total_read);
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



void write_to_file(char* filename, char* text_to_write)
{
    FILE* dest_file;
    int status;

    dest_file = fopen(filename, "w");
    if (dest_file == NULL) 
    {
        // todo: error handling
        exit(EXIT_FAILURE);
    }

    status = fwrite(text_to_write, 1, strlen(text_to_write), dest_file);
    if (status <1)
    {
        // todo: error handling
        exit(EXIT_FAILURE);
    }

    fclose(dest_file);
}


char** process_chunks(char* text, int text_size, int chunk_size_bits)
{
    int num_chunks = calculate_num_chunks(text_size, chunk_size_bits);
    
    char ** chunks = split_text_into_chunks(text, text_size, chunk_size_bits, num_chunks);

    // log chunks
    for (int i = 0; i < num_chunks; i++)
    {
        logger("chunk %d: %s", i, chunks[i]);
    }


    return chunks;
}



char** split_text_into_chunks(char* text, int text_size, int chunk_size_bits, int num_chunks) 
{
    int chunk_size = chunk_size_bits / 8;

    char** chunks = malloc(num_chunks * sizeof(char*)); // allocate memory for the chunks

    printf("Text length: %d\n", text_size);
    printf("Number of 64-bit chunks: %d\n", num_chunks);

    for (int i = 0; i < num_chunks; i++)
    {
        char* buffer = malloc(chunk_size + 1); // allocate memory for each chunk
        printf("chunk %d: ", i);
        for (int j = 0; j < chunk_size; j++)
        {
            printf("%c", text[i * chunk_size + j]);
            buffer[j] = text[i * chunk_size + j];
        }
        buffer[chunk_size] = '\0'; // add termination symbol
        chunks[i] = buffer;
        printf("\n");
    }

    return chunks;
}

int calculate_num_chunks(int text_size, int chunk_size_bit)
{
    int chunk_size = chunk_size_bit / 8;
    int num_chunks = text_size / chunk_size;

    // if text size is not a multiple of the chunk size, we need one more chunk
    if (text_size % chunk_size != 0)
    {
        num_chunks++;
    }

    return num_chunks;
}

void free_chunks(char** chunks, int num_chunks)
{
    for (int i = 0; i < num_chunks; i++)
    {
        free(chunks[i]);
    }
    free(chunks);
}