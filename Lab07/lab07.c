#include <omp.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

#define VERY_BIG

double approximate_pi(void) 
{
    uint64_t n = UINT32_MAX ;
    uint64_t no_of_points_inside = 0;
    uint8_t noOfThreads = 1;

    omp_set_num_threads(noOfThreads);

    uint32_t seed = time(NULL);

    #pragma omp parallel for reduction (+: no_of_points_inside) private(seed)
    for (uint64_t i = 0; i < n; i++) {
        double x = rand_r(&seed) * 1.0f / RAND_MAX;
        double y = rand_r(&seed) * 1.0f / RAND_MAX;
        
        double dsquared = x * x + y * y;
        if (dsquared < 1) {
            no_of_points_inside++;
        }
    }
    return 4.0 * no_of_points_inside / n;
}

int main(void) {
    
    double start = omp_get_wtime();
    double pi = approximate_pi();
    double end = omp_get_wtime();
    
    printf("> PI = %lf\n", pi);
    printf("> ellapsed time: %.10lf s\n", end - start);
    
    return 0;
}