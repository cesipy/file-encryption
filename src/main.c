#include "../include/encrypt.h"

int main(int argc, char* argv[])
{
    char* source_filename = "res/test.txt";
    char* dest_filename   = "res/result.txt";

    init_logger(LOG_FILE);

    calculate_file_size(source_filename);
    char* buf = read_from_file(source_filename);

    write_to_file(dest_filename, buf);

    free(buf);

    logger("completely printed buf");

    tear_down_logger();

    return EXIT_SUCCESS;
}