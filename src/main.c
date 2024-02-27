#include "../include/encrypt.h"

int main(int argc, char* argv[])
{
    char* filename = "res/test.txt";
    calculate_file_size(filename);
    char* buf = read_from_file(filename);

    printf("%s\ncompletely printed buf\n", buf);
    free(buf);

    return EXIT_SUCCESS;
}