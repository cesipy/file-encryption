#ifndef ENCRYPT_H
#define ENCRYPT_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "../include/logger.h"

#define CHUNK_SIZE 1024
#define LOG_FILE   "logs/log.txt"

char* read_from_file(char* filename);
void write_to_file(char* filename, char* text_to_write);

/** 
 * returns total file size in bytes.
*/
int calculate_file_size(char* filename);


typedef struct {
    unsigned long P[18];
    unsigned long S[4][256];
} blowfish_ctx_t;



unsigned long function_f(blowfish_ctx_t* ctx_t, unsigned long x); // same as in blowfish paper
void blowfish_encrypt(blowfish_ctx_t* ctx_t, unsigned long* x_l, unsigned long* x_r);
void blowfish_decrypt(blowfish_ctx_t* ctx_t, unsigned long* x_l, unsigned long* x_r);
void blowfish_init(blowfish_ctx_t* ctx_t, unsigned char* key, int len_key);

// currently not in use.
void split_message(unsigned long* x_l, unsigned long* x_r, unsigned long* x);
unsigned long chars_to_ulong(char* chars);
void ulong_to_chars(unsigned long value, char* chars);


char** process_chunks(char* text, int text_size, int chunk_size_bits);
char** split_text_into_chunks(char* text, int text_size, int chunk_size_bits, int num_chunks);
int calculate_num_chunks(int text_size, int chunk_size_bit);
void free_chunks(char** chunks, int num_chunks);


#endif