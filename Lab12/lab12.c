#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26

typedef struct {
    int a;
    int b;
    int c;
    int d;
} mat2x2_t;


mat2x2_t modular_inverse_2x2(mat2x2_t key) 
{
    int det = ((key.a * key.d - key.b * key.c) % SIZE + SIZE) % SIZE;
    mat2x2_t err = {-1, 0, 0, 0}; // error type
    if (det == 0 || det == 13 || det % 2 == 0) {
        return err;
    }
    // det_inv * det % SIZE == 1
    for (int det_inv = 1; det_inv < SIZE; det_inv++) {
        if (det_inv * det % SIZE == 1) {
            int a_inv = (det_inv * key.d % SIZE + SIZE) % SIZE;
            int b_inv = (det_inv * (-key.b) % SIZE + SIZE) % SIZE;
            int c_inv = (det_inv * (-key.c) % SIZE + SIZE) % SIZE;
            int d_inv = (det_inv * key.a % SIZE + SIZE) % SIZE;
            mat2x2_t inv = {a_inv, b_inv, c_inv, d_inv};
            return inv;
        }
    }
    return err;
}

char* encrypt(char* plaintext, size_t len, mat2x2_t key) 
{
    int* nums = (int*)malloc(sizeof(int) * len);
    char* chyperhtext = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++) {
        nums[i] = plaintext[i] - 'A';
    }
    // break into blocks of two and multiply by key
    for (int i = 0; i < len - 1; i += 2) {
        int a = nums[i];
        int b = nums[i + 1];
        int cypher_a = (key.a * a + key.b * b) % SIZE;
        int cypher_b = (key.c * a + key.d * b) % SIZE;
        chyperhtext[i] = cypher_a + 'A';
        chyperhtext[i + 1] = cypher_b + 'A';
    }
    return chyperhtext;
}

char* decrypt(char* cyphertext, size_t len, mat2x2_t key) 
{
    mat2x2_t inv = modular_inverse_2x2(key);
    if (inv.a < 0) {
        // error
        return "";
    }
    
    int* nums = (int*)malloc(sizeof(int) * len);
    char* plaintext = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++) {
        nums[i] = cyphertext[i] - 'A';
    }
    // group into 
    for (int i = 0; i < len - 1; i += 2) {
        int a = nums[i];
        int b = nums[i + 1];
        int plain_a = (inv.a * a + inv.b * b) % SIZE;
        int plain_b = (inv.c * a + inv.d * b) % SIZE;
        plaintext[i] = plain_a + 'A';
        plaintext[i + 1] = plain_b + 'A';
    }
    return plaintext;
}

void find_all_keys() {
    FILE* f = fopen("result.txt", "w");
    for (int a = 0; a < SIZE; a++) {
        for (int b = 0; b < SIZE; b++) {
            for (int c = 0; c < SIZE; c++) {
                for (int d = 0; d < SIZE; d++) {
                    mat2x2_t mat = {a, b, c, d};
                    mat2x2_t inv = modular_inverse_2x2(mat);
                    if (inv.a < 0) {
                        continue; // not invertible
                    }
                    // print inv or whatev
                }
            }
        }
    }
    fclose(f);
}


int main() {
    char* plaintext = "HIAT";
    mat2x2_t key = {3, 3, 2, 5};
    printf("%s -> %s", plaintext, decrypt(plaintext, strlen(plaintext), key));
    return 0;
}