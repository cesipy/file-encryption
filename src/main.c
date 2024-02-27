#include "../include/encrypt.h"

int main(int argc, char* argv[])
{
    char* source_filename = "res/test.txt";
    char* dest_filename   = "res/result.txt";

    calculate_file_size(source_filename);
    char* buf = read_from_file(source_filename);

    write_to_file(dest_filename, buf);

    printf("%s\ncompletely printed buf\n", buf);
    free(buf);

    return EXIT_SUCCESS;
}