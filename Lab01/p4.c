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
#include <stdlib.h>
#include <time.h>
#include <math.h>

int isInsideCircle(double x, double y);
double calculatePi(unsigned int N);

int main(){

    clock_t clock_st;
    double elapsed_time;

    clock_st = clock();

    /* ---------- call for the problem ---------- */
    srand(time(NULL));

    unsigned int N = 100000000;
    // printf("For number of points\nN = ");
    // scanf_s("%d", &N);

    printf("PI = %lf\n", calculatePi(N));
    /* ----- end operations for the problem ----- */

    elapsed_time = (double)(clock() - clock_st) / CLOCKS_PER_SEC;

    printf("> Elapsed time is %lf\n", elapsed_time);

}

int isInsideCircle(double x, double y)
{
    return ((x * x) + (y * y)) <= 1.0;
}

double calculatePi(unsigned int N)
{
    unsigned int M = 0;
    for (unsigned int i = 0; i < N; i++)
    {
        double x = rand() * 1.0 / RAND_MAX;
        double y = rand() * 1.0 / RAND_MAX;
        if (isInsideCircle(x, y))
            M++;
    }

    return 4.0 * M / N;
}
