/***********************************************
*         Benedek Balazs - Group 30444
*                   ~ 2022 ~
************************************************
*
*       Technical University of Cluj-Napoca
*    Faculty of Automation and Computer Science
*               
*              Parallel Programming
*
*     _     _            _        ____   ____
*    | |__ | | ___  ___ |_| ___  /    \ /    \
*    |    \| |/__ \| __|| |/   \ \__'  |\__'  |
*    |  .  | |  .  |__ || |  .  | __|  | __|  |
*    \____/|_|\___/|___||_|\___/ |____/ |____/
*
************************************************
*              github.com/blasio99
*
************************************************/

/*
* Problem 2 - Compute the entropy of a binary random sequence
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRUE  1u 
#define FALSE 0u

/* Fail macro to print error message */
#define FAIL() \
        do \
        { \
            printf("N is smaller than 0"); \
        } while (0);

/* Assert test macro */
#define _assert(test) \
        do \
        { \
            if (!(test)) \
            { \
                FAIL(); \
                return ; \
             } \
        } while(0)

typedef unsigned char boolean;

unsigned int numberOfOneBits(unsigned char number);
void computeOnesAndZeros(unsigned int N, unsigned char* array, unsigned int* O, unsigned int* Z);
double computeEntropy(unsigned int N, unsigned int O, unsigned int Z);

int main(){

    clock_t clock_st;
    double elapsed_time;

    clock_st = clock();

    /* ---------- call for the problem ---------- */
    srand(time(NULL));

    unsigned int N = 10000;
    unsigned int O = 0;
    unsigned int Z = 0;

    unsigned char* S = (unsigned char*)malloc(sizeof(unsigned char) * N);
    
    for (unsigned int i = 0; i < N; ++i)
    {
        S[i] = rand() % 256;
    }
    computeOnesAndZeros(N, S, &O, &Z);

    printf("entropy=%lf\n", computeEntropy(N, O, Z));
    /* ----- end operations for the problem ----- */

    elapsed_time = (double)(clock() - clock_st) / CLOCKS_PER_SEC;

    printf("> Elapsed time is %lf\n", elapsed_time);

}

unsigned int numberOfOneBits(unsigned char number)
{
    unsigned int count = 0;

    for (int i = 0; i < 8; ++i)
    {
        count += (number & (1 << i)) >> i;
    }
    return count;
}

void computeOnesAndZeros(unsigned int N, unsigned char* array, unsigned int* O, unsigned int* Z)
{
    _assert(N > 0);

    for (unsigned int i = 0; i < N; ++i)
    {
        *O += numberOfOneBits(array[i]);
    }
    *Z = (N << 3) - *O;
}

double computeEntropy(unsigned int N, unsigned int O, unsigned int Z)
{
    unsigned int T = N << 3;

    double OPerT = O * 1.0 / T;
    double ZPerT = Z * 1.0 / T;

    printf("OPerT = %lf\nZPerT = %lf\n", OPerT, ZPerT);

    return -OPerT * log(OPerT) / log(2) - ZPerT * log(ZPerT) / log(2);
}