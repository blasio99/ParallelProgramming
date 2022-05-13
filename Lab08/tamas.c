/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int globalNr = 0;

bool containsDigits(int n, int digits[]) {
    // printf("%d\n", n);
    int cnt = 0;
    int tempN = n;
    int freq[10];
    
    for (int i = 0; i < 10; i++)
        freq[i] = 0;
    for (int i = 0; i < 8; i++)
        freq[digits[i]]++;
        
    while (tempN != 0) {
        freq[tempN % 10]--;
        tempN /= 10;
    }
    
    for (int i = 0; i < 10; i++) {
        if (freq[i] < 0)
            return false;
    }
    return true;
}

void isVampire(int n) {
    int digits[8], tempDigits[8];
    for (int i = 0; i < 8; i++)
        digits[i] = 0;
    int tempN = n;
    int index = 0;
    while (tempN != 0) {
        digits[index++] = tempN % 10;
        tempN /= 10;
    }
    
    int lim = sqrt(n);
    
    for (int i = 1000; i < lim; i++) {
        for (int j = 0; j < 8; j++) {
            tempDigits[j] = digits[j];
        }
        
        tempN = n;
        if (containsDigits(i, tempDigits)) {
            int secondFreq[10];
            
            for (int j = 0; j < 10; j++)
                secondFreq[j] = 0;
            
            int tempI = i;
            
            while (tempN != 0) {
                secondFreq[tempN % 10]++;
                tempN /= 10;
            }

            while (tempI != 0) {
                secondFreq[tempI % 10]--;
                tempI /= 10;
            }
          
            // if (i == 1107) {
            //     printf("\n");
            //     for (int i = 0; i < 10; i++)
            //         printf("%d ", secondFreq[i]);
            // }
            
            int secondNb = n / i;
            if (i * secondNb == n){
                // printf("%d %d\n", i, secondNb);
                // printf("HERE\n");
                int tempSecond = secondNb;
                while (tempSecond != 0) {
                    secondFreq[tempSecond % 10]--;
                    tempSecond /= 10;
                }
                
                bool flag = false;
                for (int j = 0; j < 10; j++) {
                    // printf("%d %d\n", j, secondFreq[j]);
                    if (secondFreq[j] != 0)
                        flag = true;
                }
                if (!flag)
					globalNr++;
                  //  printf("%d\n", n);
            }
        }
    }
    
}

int main()
{
	clock_t begin = clock();
    for (int i = 10000000; i <= 15000000; i++)
        isVampire(i);
	
	clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("%d\n", globalNr);
    printf("\nTime elapsed in milliseconds: %f\n", time_spent);
    return 0;
}
