#include "../include/logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

FILE* file;

void init_logger(char* filename)
{
    file = fopen(filename, "a");       // in append mode
    // todo: error handling
    // dreturn file;
}


void tear_down_logger()
{
    fclose(file);
    // todo: error handling
    
}

void logger(const char* format, ...) 
{
    va_list args;
    va_start(args, format);

    char* message;
    vasprintf(&message, format, args); // allocate and format the message

    time_t now;
    time(&now);
    char* time_str = ctime(&now);
    time_str[strlen(time_str)-1] = '\0'; // remove newline from end of ctime()

    fprintf(file, "%s: %s\n", time_str, message);

    free(message); // free the allocated message string
    va_end(args);
}