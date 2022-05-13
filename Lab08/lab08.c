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

#include <omp.h>
#include "stdio.h"
#include "stdlib.h"
#include <time.h>
#include <math.h>

/* defines */
#define TRUE  (1u)              /* boolean true */
#define FALSE (0u)              /* boolean false */
#define NUMBER_LENGTH (8)       /* the length of a number */
#define FACTOR_LENGTH (4)       /* the length of a divisor */
#define RANGE_MIN (10000000)    /* the minimum value of the range */
#define RANGE_MAX (20000000)    /* the maximum value of the range */
#define DIV_MIN (1000)          /* the smallest divisor */
#define DIV_MAX (9999)          /* the greatest divisor */
#define NR_OF_THREADS (24)      /* the number of threads to make it parallel */
#define UNAVAILABLE (99)        /* the define for a used digit - at verification of the presence of a divisor digit in the number */

/* typedefs */
typedef unsigned char boolean;
typedef double float64;

/* global variables */
int sum = 0;
int partialSum[NR_OF_THREADS] = {0};
boolean vampireNumbers[RANGE_MAX - RANGE_MIN + 1] = {FALSE};

/* function headers */
boolean checkDigits(int* digitsNr, int divisor1, int divisor2);
boolean checkVampire(int nr);
void vampire(void);
void printResults(void);

/* main function */
void main(void)
{
	omp_set_nested(1);
	omp_set_dynamic(0);
	
    float64 start = omp_get_wtime();    /* get the start time */
	omp_set_num_threads(NR_OF_THREADS); /* set the number of threads */
    vampire();                          /* solution */
	float64 end = omp_get_wtime();      /* get the end time */

    printResults();                     /* print the results, and the vampire numbers into file */

    printf("> ellapsed time: %.10lf sec\n", end - start);
}

void vampire(void)
{   
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = RANGE_MIN; i <= RANGE_MAX; ++i)
        {
            if(TRUE == checkVampire(i))
            {
                partialSum[omp_get_thread_num()] ++;    /* sum of each thread */
                vampireNumbers[i - RANGE_MIN] = TRUE;   /* bitmap for vampire numbers */
                                                        /* i - RANGE_MIN to start from position 0 */
            }
        }
    }
}

boolean checkVampire(int nr)
{	
	int divisors[10000] = {0};
	int nrOfDiv = 0;
	int digits[NUMBER_LENGTH] = {0};
	int auxNr = nr;

	for (int i = 0; i < NUMBER_LENGTH; ++i)
	{
		digits[i] = auxNr % 10;
		auxNr /= 10;
	}

	for (int i = DIV_MIN; i <= DIV_MAX; ++i)
	{
		if (0 == nr % i)
		{	
			divisors[nrOfDiv++] = i;
		}
	}

	for(int i = 0; i < nrOfDiv - 1; ++i)
    {
		for (int j = i; j < nrOfDiv; ++j)
		{	
			if (divisors[i] * divisors[j] == nr)
			{
                if (checkDigits(digits, divisors[i], divisors[j]))
                {
                    return TRUE;
                }
			}
		}
    }
	return FALSE;
}

boolean checkDigits(int* digitsNr, int divisor1, int divisor2)
{	
	int auxDigits[NUMBER_LENGTH];
    
    /* 2 divisors cannot terminate with 0 at the same time */
    if((0 == divisor1 % 10) && (0 == divisor2 % 10))
    {
        return FALSE;
    }
    
    /* create an auxiliar digit vector, to not change the digitsNr */
    for (int i = 0; i < NUMBER_LENGTH; auxDigits[i] = digitsNr[i], i++);
    
    /* checking the presence of all divisor digits in the original number */
	for (int i = 0; i < FACTOR_LENGTH; ++i)
	{
		int digit1 = (int)(divisor1 % 10);
		int digit2 = (int)(divisor2 % 10);
		
		divisor1 /= 10;
		divisor2 /= 10;

		boolean foundDigit1 = FALSE;
		boolean foundDigit2 = FALSE;

		for (int j = 0; j < NUMBER_LENGTH; ++j)
		{
			if ((auxDigits[j] == digit1) && (FALSE == foundDigit1))
			{
				foundDigit1 = TRUE;
				auxDigits[j] = 99;  /* set to 99, as we do not want to repeat the digits */
			}

			if ((auxDigits[j] == digit2) && (FALSE == foundDigit2))
			{
				foundDigit2 = TRUE;
				auxDigits[j] = 99;  /* set to 99, as we do not want to repeat the digits */
			}
		}
		
		if ((FALSE == foundDigit1) || (FALSE == foundDigit2))
		{
            /* if one of the digits is not found then it is not vampire */
			return FALSE;
		}
	}
	return TRUE;
}

void printResults(void)
{
    for(int i = 0; i < NR_OF_THREADS; ++i)
    {
        printf("> Thread %d found %d numbers\n", i, partialSum[i]);
        sum += partialSum[i];
    }
    printf("> Sum == %d \n", sum);

    FILE *fp = fopen("results.txt", "w");

    for(int i = 0; i < RANGE_MAX - RANGE_MIN; ++i)
    {
        if(TRUE == vampireNumbers[i])           /* if the number is vampire */
        {
            fprintf(fp, "%d\n", i + RANGE_MIN); /* i + RANGE_MIN because we have started from position 0 in the bitmap */
        }
    }
    fclose(fp);
}
