#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define RANDOM_ARR_LENGTH 1000000

void printperfectNumberSearch(int arr[], int cnt);
void perfectNumberSearch(int a, int b);

int main(int argc, char* argv[]) 
{
    perfectNumberSearch(atoi(argv[1]),atoi(argv[2]));
}

void printperfectNumberSearch(int arr[], int cnt){
    printf("Array of prime numbers is:\n");
    for(int i=0; i<cnt-1; i++){
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[cnt-1]);
}

void perfectNumberSearch(int a, int b){
    int arr[10];
    int sum;
    int cnt =0;
    for(int x = a; x <= b; x++){
        sum=0;
        for(int d = 1; d <= x/2; d++){
            if(x%d == 0){
                sum+=d;
            }
        }
        if(sum == x){
            arr[cnt++] = x;
        }
    }
    printperfectNumberSearch(arr, cnt);
}