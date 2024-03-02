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

    /*-------------------------------------------*/

    blowfish_ctx_t ctx;
    unsigned long x_l = 10;
    unsigned long x_r = 23;
    char* key = "completely random key";
    int key_len = 21;

    blowfish_init(&ctx, (unsigned char*)key, key_len);

    blowfish_encrypt(&ctx, &x_l, &x_r);
    logger("encrypted: %lu %lu", x_l, x_r);

    blowfish_decrypt(&ctx, &x_l, &x_r);
    logger("decrypted: %lu %lu", x_l, x_r);

    tear_down_logger();

    return EXIT_SUCCESS;
}