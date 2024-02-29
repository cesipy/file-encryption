#include "../include/encrypt.h"


void init(blowfish_ctx_t* ctx_t, unsigned char* key, int len_key)
{
    int S_i = 4;
    int S_j = 256;
    int P_i = 18;

    for (int i=0; i<S_i; i++)
    {
        for (int j=0; j<S_j; j++)
        {
            ctx_t->S[i][j] = original_S[i][j];
        }
    }

    for (int i=0; i<P_i; i++)
    {
        ctx_t->P[i] = original_P[i];
    }

}



unsigned long function_f(blowfish_ctx_t* ctx_t, unsigned long x) 
{
    // divide c into four eight-bit quartes
    unsigned short d = x & 0x00FF;      // bitwise AND with 00FF = 255 = 8 bits
    x = x >> 8;
    unsigned short c = x & 0x00FF;
    x = x >> 8;
    unsigned short b = x & 0x00FF;
    x = x >> 8;
    unsigned short a = x & 0x00FF;

    unsigned long y = ctx_t->S[0][a] + ctx_t->S[1][b];
    y = y ^ ctx_t->S[2][c];
    y = y + ctx_t->S[3][d];
}



// todo: use pointer instead of real values
void blowfish_encrypt(blowfish_ctx_t* ctx_t, unsigned long x)
{
    // split into left and right
    unsigned long x_r = x & 0xFFFFFFFF;   
    x = x >> 32;
    unsigned long x_l = x & 0xFFFFFFFF;

    unsigned long temp;

    for (int i=0; i<16; i++)
    {
        x_l = x_l ^ ctx_t->P[i];
        x_r = function_f(ctx_t, x_l) ^ x_r;
        

        temp = x_l;
        x_l = x_r;
        x_r = temp;
        
    }

    temp = x_l;
    x_l = x_r;
    x_r = temp;

    x_r = x_r ^ ctx_t->P[1];
    x_l = x_l ^ ctx_t->P[0];
}
