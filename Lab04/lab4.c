#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>

#define TRUE  1u 
#define FALSE 0u
#define LOW 11
#define HIGH 1e+8
#define MICRO_SEC_TO_SEC (float)1000000.0f

typedef unsigned char boolean;

/* for simplicity the no. of processes is defined here,
 * But a better idea is to read it from the command line */

void do_work(int i, int PROCESSSES);
int64_t difftimespec_us(const struct timespec after, const struct timespec before);

int main(int argc, char** argv)
{
	int i, pid;
	/* Take initial time here */
	/* Use clock_gettime(). Do NOT use clock() */
	struct timespec start;
	struct timespec stop;

	clock_gettime(CLOCK_MONOTONIC, &start);

	int PROCESSES = atoi(argv[1]);
	for(i = 0; i < PROCESSES; i++)
	{
		pid = fork();
		if(pid < 0) /* some error occurred – fork failed */
		{
			printf("Error");
			exit(-1);
		}
		if(pid == 0) /* child process code */
		{
			do_work(i, PROCESSES);
			exit(0);
		}
		/* do not place any wait() call here */
	}
	
	/* wait for all processes to finish their execution */
	for(i = 0; i < PROCESSES; i++)
		wait(NULL);
	
	/* Take final time here */
	/* Use clock_gettime(). Do NOT use clock() */
	/* Compute the execution time*/
	clock_gettime(CLOCK_MONOTONIC, &stop);
	printf("\n$> execution time (s): %lf\n", (difftimespec_us(stop, start) / MICRO_SEC_TO_SEC));
}

boolean isPrime(unsigned int number)
{
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

boolean checkCircular(unsigned int number)
{
	unsigned int cnt;
	unsigned int temp;

	cnt = 0;
	temp = number;
	while (0 != temp) {
		++ cnt;
		temp /= 10;
	}

	temp = number;
	while (TRUE == isPrime(temp)) {
		unsigned int rem = temp % 10;
		unsigned int div = temp / 10;
		temp = (pow(10, cnt - 1)) * rem + div;

		if (temp == number)
			return TRUE;
	}
	return FALSE;
}

void circularPrimesInRange(unsigned int A, int P, unsigned int B)
{
	unsigned int val = A;
	while (val < B)
	{
		if (checkCircular(val))
		{
			printf("%d ", val);
		}
		else
		{
			/* Do nothing */
		}
		val += P;
	}
}

/* this function is executed by each process */
void do_work(int i, int PROCESSES)
{
	//printf("Hello there, from process %d! \n", i);
	/* rest of the code goes here */
	circularPrimesInRange(LOW + 2*i, 2*PROCESSES, HIGH);
}

int64_t difftimespec_us(const struct timespec after, const struct timespec before)
{
	    return ((int64_t)after.tv_sec - (int64_t)before.tv_sec) * (int64_t)1000000
		             + ((int64_t)after.tv_nsec - (int64_t)before.tv_nsec) / 1000;
}
