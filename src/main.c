#include "../include/encrypt.h"
#include <openssl/aes.h>

int main(int argc, char* argv[])
{
    char* source_filename = "res/test.txt";
    char* dest_filename   = "res/result.txt";

    init_logger(LOG_FILE);

    // Read the file into a buffer
    char* buf = read_from_file(source_filename);

    blowfish_ctx_t ctx;
    char* key = "completely random key";
    int key_len = 21;
    
    unsigned long x_l, x_r;
    x_l = 123;
    x_r = 456;

    // Initialize the Blowfish context with the key
    blowfish_init(&ctx, (unsigned char*)key, key_len);

    blowfish_encrypt(&ctx, &x_l, &x_r);
    logger("encrypted: l: %lu; r: %lu", x_l, x_r);

    blowfish_decrypt(&ctx, &x_l, &x_r);
    logger("decrypted: l: %lu; r: %lu", x_l, x_r);


    free(buf);

    tear_down_logger();

    return EXIT_SUCCESS;
}