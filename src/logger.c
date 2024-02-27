#include "../include/logger.h"
#include <stdio.h>

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

void logger(const char* message) 
{
    time_t now;
    time(&now);
    fprintf(file, "%s: %s\n\n", ctime(&now), message);
}