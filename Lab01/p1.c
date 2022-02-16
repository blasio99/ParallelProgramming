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
* Problem 1 - Naive prime number search
*/

#include <stdio.h>
#include <time.h>

#define TRUE  1u 
#define FALSE 0u

/* Fail macro to print error message */
#define FAIL() \
        do \
        { \
            printf("A is a bigger number than B"); \
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

boolean isPrime(unsigned int number);
void findAllPrimes(unsigned int A, unsigned int B);


int main(){

    clock_t clock_st;
    double elapsed_time;

    clock_st = clock();

    /* ---------- call for the problem ---------- */
    unsigned int    A = 2;
    unsigned int    B = 100;

    findAllPrimes(A, B);
    /* ----- end operations for the problem ----- */

    elapsed_time = (double)(clock() - clock_st) / CLOCKS_PER_SEC;

    printf("> Elapsed time is %lf\n", elapsed_time);

}

boolean isPrime(unsigned int number){

    /* let's cover all cases */
    if (2 == number)
    {
        return TRUE;
    }
    else 
    {
        /* go ahead */
    }

    if ((2 > number) || (0 == number % 2))
    {
        return FALSE;
    }
    else 
    {
        /* go ahead */
    }

    for (unsigned int i = 3; (i * i) <= number; i += 2)
    {
        if (0 == number % i)
        {
            return FALSE;
        }
        else
        {
            /* continue execution */
        }
    }
    return TRUE;
}

void findAllPrimes(unsigned int A, unsigned int B)
{
    _assert(A < B);

    for (unsigned int i = A; i <= B; ++i)
    {
        if (TRUE == isPrime(i))
        {
            printf("%d ", i);
        }
        else
        {
            /* do nothing */
        }
    }
}