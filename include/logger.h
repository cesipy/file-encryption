#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>

void logger(const char* format, ...);
void init_logger(char* filename);
void tear_down_logger();

#endif