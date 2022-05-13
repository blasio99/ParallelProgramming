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
#include <stdlib.h>

/* defines */
#define SIZE_OF_KEYWORD 14

/* global variables */
char keyword[SIZE_OF_KEYWORD] = "BENEDEKBALAZS";
int seed;
int alphabet[256];
int random[1024] = {0};

/* prototypes */
int computeSeed(char keyword[]);
void swap(int posX, int posY);
void encryptFile();
void decryptFile();

/* the main function of the file */
int main()
{
    /* the encryption part of the assignment */
    encryptFile();

    /* the decryption part of the assignment */
    decryptFile();

    return 0;
}

void encryptFile()
{
    FILE* readFile = fopen("Lab_09.pdf", "rb");
    FILE* writtenFile = fopen("Lab_09.enc", "wb");

    fseek(readFile, 0, SEEK_END);
    long size = ftell(readFile);
    fseek(readFile, 0, SEEK_SET);
    unsigned char character;
    unsigned char newCharacter;

    seed = computeSeed(keyword);
    srand(seed);

    /* initializing the alphabet and frequency arrays */
    for (int i = 0; i < 256; alphabet[i] = i, ++i);

    /* creating the vector of random values in range [0 - 255] */
    for (int i = 0; i < 1024; random[i] = (int)rand() % 256, ++i);

    /* 
    *  performing a swap between every 2 position, where these 2 values 
    *  are taken from the i-th, and (i + 1)st position of the random vector 
    */
    for(int i = 0; i < 1023; ++i)
    {
        swap(i, i + 1);
    }

    /* print the value and its encrypted mate */
    for(int i = 0; i < 256; ++i)
    {
        printf("> %d = %d\n", i, alphabet[i]);
    }

    /* read the characters from the pdf, and write the encrypted pair of it */
    for (long i = 0; i < size; ++i)
    {
        fread(&character, 1, 1, readFile);
        newCharacter = alphabet[character];
        fwrite(&newCharacter, 1, 1, writtenFile);
    }

    fclose(readFile);
    fclose(writtenFile);
}

void decryptFile()
{
    FILE* readFile = fopen("Lab_09.enc", "rb");
    FILE* writtenFile = fopen("Lab09_Enc_Dec.pdf", "wb");

    fseek(readFile, 0, SEEK_END);
    long size = ftell(readFile);
    fseek(readFile, 0, SEEK_SET);
    unsigned char character;
    unsigned char newCharacter;

    srand(seed);

    /* initializing the alphabet and frequency arrays */
    for (int i = 0; i < 256; alphabet[i] = i, ++i);

    /* creating the vector of random values in range [0 - 255] */
    for (int i = 0; i < 1024; random[i] = (int)rand() % 256, ++i);

    /* 
    *  performing a swap between every 2 position, where these 2 values 
    *  are taken from the i-th, and (i - 1)st position of the random vector 
    */
    for(int i = 1023; i > 0; --i)
    {
        swap(i, i - 1);
    }

    /* print the value and its decrypted mate */
    for(int i = 0; i < 256; ++i)
    {
        printf("> %d = %d\n", i, alphabet[i]);
    }

    /* read the characters from the encrypted file, and write the decrypted pair of it */
    for (long i = 0; i < size; ++i)
    {
        fread(&character, 1, 1, readFile);
        newCharacter = alphabet[character];
        fwrite(&newCharacter, 1, 1, writtenFile);
    }

    fclose(readFile);
    fclose(writtenFile);
}

/* computing the seed by keyword */
int computeSeed(char keyword[])
{
    int seed = 0;

    printf("> Keyword: ");

    for (int i = 0; i < SIZE_OF_KEYWORD; ++i)
    {
        seed += keyword[i];
        printf("%c", keyword[i]);
    }

    printf("\n> Seed = %d\n", seed);
    
    return seed;
}

/* the swap function */
void swap(int posX, int posY)
{
    int temp = alphabet[random[posX]];
    alphabet[random[posX]] = alphabet[random[posY]];
    alphabet[random[posY]] = temp;
}
