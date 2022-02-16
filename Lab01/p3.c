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
* Problem 3 – Compute the value of PI (π)
*/

#include <stdio.h>
#include <time.h>
#include <math.h>

double computePi(long N);

int main(){

    clock_t clock_st;
    double elapsed_time;

    clock_st = clock();

    /* ---------- call for the problem ---------- */
    long N = 50000000;

    printf("PI with N=%d is \n", N);
    printf("%0.15lf\n", computePi(N));
    /* ----- end operations for the problem ----- */

    elapsed_time = (double)(clock() - clock_st) / CLOCKS_PER_SEC;

    printf("> Elapsed time is %lf\n", elapsed_time);

}

double computePi(long N)
{
    double PI = 0;

    for (long i = 0; i < N; i++)
    {
        PI += 4.0 / (1 + pow(((i + 0.5) / N), 2));
    }

    return PI / N;
}
