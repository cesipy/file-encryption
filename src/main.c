#include "../include/encrypt.h"
#include <openssl/aes.h>

void convert_charChunks_to_longChunks(char** chunks, int num_chunks, unsigned long* long_chunks)
{
    for (int i=0; i<num_chunks; i++)
    {
        long_chunks[i] = chars_to_ulong(chunks[i]);
    }
}

void convert_longChunks_to_charChunks(unsigned long* long_chunks, int num_chunks, char** chunks)
{
    for (int i=0; i<num_chunks; i++)
    {
        ulong_to_chars(long_chunks[i], chunks[i]);
    }
}


int main(int argc, char* argv[])
{
    char* source_filename = "res/test.txt";
    char* dest_filename   = "res/result.txt";

    init_logger(LOG_FILE);

    // Read the file into a buffer
    char* buf = read_from_file(source_filename);
    int len = strlen(buf);

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
    
    char** chunks = process_chunks(buf, len, 64);

    int num_chunks = calculate_num_chunks(len, 64);
    char** chunks_temp = malloc(num_chunks * sizeof(char*));
    unsigned long* chunks_unsigned_long = malloc(num_chunks * sizeof(unsigned long));


    convert_charChunks_to_longChunks(chunks, num_chunks, chunks_unsigned_long);

    for (int i=0; i<num_chunks; i++)
    {
            logger("(unsigned) chunk %d: %lu", i, chunks_unsigned_long[i]);
    }


    for (int i=0; i<num_chunks; i++)
    {
        x_l = chunks_unsigned_long[i];
        x_r = chunks_unsigned_long[i];
        blowfish_encrypt(&ctx, &x_l, &x_r);
        logger("encrypted chunk %d: %llu", i, &x_l);
    }

    for (int i=0; i<num_chunks; i++) 
    {
        x_l = chunks_unsigned_long[i];
        x_r = chunks_unsigned_long[i];
        blowfish_decrypt(&ctx, &x_l, &x_r);
        logger("decrypted chunk %d: %lu", i, &x_l);
    }

    convert_longChunks_to_charChunks(chunks_unsigned_long, num_chunks, chunks_temp);

    for (int i=0; i<num_chunks; i++)
    {
        logger("(char from unsigned/after encryption) chunk %d: %s", i, chunks_temp[i]);
    }

    free(chunks);
    free(buf);
    tear_down_logger();

    return EXIT_SUCCESS;
}
