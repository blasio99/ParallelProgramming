#include <stdio.h>
#include <stdint.h>

#define MULTIPLY(A, B) A * B

int main(){

    int8_t a = 2;
    uint32_t b = 3;
    uint8_t res = MULTIPLY(++a + 1, b++ + 1);

    printf("%d", res);
}