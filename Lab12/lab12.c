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

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {            /*     ___________      */
    unsigned char a;        /*    |  a  |  b  |     */
    unsigned char b;        /*    |_____|_____|     */
    unsigned char c;        /*    |  c  |  d  |     */
    unsigned char d;        /*    |_____|_____|     */
} mat2x2_t;                 /*      1. figure       */

#define SIZE 26
#define ERROR_MATRIX_2X2 ((mat2x2_t){-1, -1, -1, -1})
#define ERROR_MESSAGE ((char*)"[ERROR] Inverse matrix error")


mat2x2_t modular_inverse_2x2(mat2x2_t key);                 /* to create the inverse matrix */
char* encrypt(char* plaintext, size_t len, mat2x2_t key);   /* to encrypt the given plaintext, of size len, with the key "key" */
char* decrypt(char* cyphertext, size_t len, mat2x2_t key);  /* to decrypt the given plaintext, of size len, with the key "key" */
void find_all_keys();                                       /* create 2 files of all possible KEYS, and their INVERSES */
void find_all_messages(char* cyphertext);                   /* find all possible messages for "HIAT" */

int main() 
{
    char* paintext_encrypt = "HELP";
    char* paintext_decrypt = "HIAT";

    mat2x2_t key = {3, 3, 2, 5}; /* helper to find the correct word */

    find_all_keys();

    printf("> Encrypt: %s -> %s\n", paintext_encrypt,                                           /* Plain text to be encrypted: e.g. HELP */
                                    encrypt(paintext_encrypt, strlen(paintext_encrypt), key));  /* The result of encryption:   e.g. HIAT */
    printf("> Decrypt: %s -> %s\n", paintext_decrypt,                                           /* Plain text to be decrypted: e.g. HIAT */
                                    decrypt(paintext_decrypt, strlen(paintext_decrypt), key));  /* The result of decryption:   e.g. HELP */

    find_all_messages(paintext_decrypt);

    return 0;
}

mat2x2_t modular_inverse_2x2(mat2x2_t key) 
{
    int det = ((key.a * key.d - key.b * key.c) % SIZE + SIZE) % SIZE; /* formula provided by the teacher */
    
    if ((0  == det) || (13 == det) || (0 == det % 2))  /* rules for non-invertible matrices */
    {
        return ERROR_MATRIX_2X2;
    }
    else
    {
        /* Go ahaed */
    }

    for (int det_inv = 1; det_inv < SIZE; ++det_inv)
    {
        if (1 == (det_inv * det) % SIZE) 
        {
            int a_inv = (det_inv * key.d    % SIZE + SIZE) % SIZE;
            int b_inv = (det_inv * (-key.b) % SIZE + SIZE) % SIZE;
            int c_inv = (det_inv * (-key.c) % SIZE + SIZE) % SIZE;
            int d_inv = (det_inv * key.a    % SIZE + SIZE) % SIZE;
            
            /* return the inverse matrix */
            return (mat2x2_t){a_inv, b_inv, c_inv, d_inv};
        }
    }
    return ERROR_MATRIX_2X2; /* return the error matrix */
}

/* TASK 2 */
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
    mat2x2_t inv = modular_inverse_2x2(key);    /* Get the inverse matrix of the key */

    if (inv.a == ERROR_MATRIX_2X2.a) 
    {
        return ERROR_MESSAGE;  /* Check if there is no error during inversion */
    }
    
    int* nums = (int*)malloc(sizeof(int) * len);
    char* plaintext = (char*)malloc(sizeof(char) * len);
    
    for (int i = 0; i < len; ++i) 
    {
        nums[i] = cyphertext[i] - 'A';
    }
    
    /* group into */
    for (int i = 0; i < len - 1; i += 2) 
    {
        int a = nums[i];
        int b = nums[i + 1];
        int plain_a = (inv.a * a + inv.b * b) % SIZE;
        int plain_b = (inv.c * a + inv.d * b) % SIZE;
        
        plaintext[i]     = plain_a + 'A';
        plaintext[i + 1] = plain_b + 'A';
    }
    return plaintext;
}

/* TASK 1 */
void find_all_keys() 
{
    FILE* file_ptr    = fopen("KEYS_2x2.txt", "w");
    FILE* fileInv_ptr = fopen("INVKEYS_2x2.txt", "w");

    int total = 0;

    if ((NULL == file_ptr) || (NULL == fileInv_ptr)) 
    {   
        printf("[Error] Could not open file\n"); 
        exit(-1);
    } 

    /* brute force method */
    for (int a = 0; a < SIZE; ++a) 
    {
        for (int b = 0; b < SIZE; ++b) 
        {
            for (int c = 0; c < SIZE; ++c) 
            {
                for (int d = 0; d < SIZE; ++d) 
                {
                    mat2x2_t mat = {a, b, c, d};
                    mat2x2_t inv = modular_inverse_2x2(mat);

                    if (inv.a == ERROR_MATRIX_2X2.a) 
                    {   
                        continue; /* not invertible matrix */
                    }

                    ++ total;

                    /* print the possible keys into a file */
                    fprintf(file_ptr,    "%c%c%c%c\n", (char)mat.a + 'A', (char)mat.b + 'A', (char)mat.c + 'A', (char)mat.d + 'A');     
                    /* print the inverses of the keys into a file */
                    fprintf(fileInv_ptr, "%c%c%c%c\n", (char)inv.a + 'A', (char)inv.b + 'A', (char)inv.c + 'A', (char)inv.d + 'A');     
                }
            }
        }
    }
    fclose(file_ptr);
    fclose(fileInv_ptr);

    printf("> Total number of keys: %d\n", total);
}

/* TASK 3 */
void find_all_messages(char* cyphertext)
{
    FILE* fileInv_ptr = fopen("INVKEYS_2x2.txt", "r");
    FILE* fileMsg_ptr = fopen("MESSAGES_2x2.txt", "w");

    mat2x2_t inputMat;
    int total = 0;

    if ((NULL == fileInv_ptr) || (NULL == fileMsg_ptr)) 
    {   
        printf("[Error] Could not open file\n"); 
        exit(-1);
    }

    while(EOF != fscanf(fileInv_ptr, "%c%c%c%c\n", &inputMat.a, &inputMat.b, &inputMat.c, &inputMat.d))
    {
        inputMat.a -= 'A';
        inputMat.b -= 'A';
        inputMat.c -= 'A';
        inputMat.d -= 'A';

        char * result = decrypt(cyphertext, strlen(cyphertext), inputMat);

        fprintf(fileMsg_ptr, "%c%c%c%c\n", result[0], result[1], result[2], result[3]);
    }

    fclose(fileInv_ptr);
    fclose(fileMsg_ptr);
}