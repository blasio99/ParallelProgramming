#include <iostream>
#include "mpi.h"
#include <stdio.h>
#include "stdlib.h"
#include <vector>

#define HISTOGRAM_SIZE 256
#define OUTPUT_FILE_HEIGHT 22 /* this value is only for me to start from the bottom of notepad*/

/* MPI_Init & MPI_Finalize are called in MPI_HelloWorld, where the main function can be find as well */

int rank;
int histogramArray[HISTOGRAM_SIZE] = { 0 };
int result[HISTOGRAM_SIZE] = { 0 };
int no_of_processes = 0;
int* tmpArray;
std::vector<int> inputs;
size_t size;

void read_input(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please specify input file.");
        exit(2);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);

    if (rank == 0) {
        char* inputFile = argv[1];

        FILE* ifp = fopen(inputFile, "r");
        int value = 0;
        while (fscanf(ifp, "%d\n", &value) == 1) {
            inputs.push_back(value);
        }
        fclose(ifp);
        MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
}

auto calculate_histogram() -> void {
    int chunk_len = size / no_of_processes;
    int chunk_lenRemainder = size % no_of_processes;
    int toSendSize;
    int toSendSizeHelper = size - ((no_of_processes - 1) * chunk_len);

    int* toSendSizePerProcess = new int[no_of_processes];
    int* offsets = new int[no_of_processes];

    int sz = 0;
    for (int i = 0; i < no_of_processes; i++) {
        toSendSize = (chunk_lenRemainder-- > 0) ? chunk_len + 1 : chunk_len;

        toSendSizePerProcess[i] = toSendSize;
        offsets[i] = sz;
        sz += toSendSize;

        if (rank == 0) {
            printf("%d size %d, offs %d\n", i, toSendSizePerProcess[i], offsets[i]);
        }
    }

    int* processChunk = new int[toSendSizePerProcess[rank]];
    MPI_Scatterv(&inputs[0], toSendSizePerProcess, offsets, MPI_INT, processChunk, toSendSizePerProcess[rank], MPI_INT, 0, MPI_COMM_WORLD);

    /* calculation */
    for (unsigned int i = 0; i < toSendSizePerProcess[rank]; i++) {
        if (processChunk != NULL) {
            histogramArray[processChunk[i]]++;
        }
    }
    MPI_Reduce(histogramArray, result, HISTOGRAM_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}

auto print_output(int argc, char* argv[]) -> void {
    if (rank == 0) {

        /* Histogram Result == the file containging the appearances, the histogram */
        FILE* ofp = fopen("HistogramResult.txt", "w");
        for (int i = 0; i < HISTOGRAM_SIZE; i++) {
            fprintf(ofp, "%d\t: %d\t => ", i, result[i]);
            for (int v = 0; v < result[i]; v++) {
                fprintf(ofp, "_");
            }
            fprintf(ofp, "\n");
        }
        fclose(ofp);

        /* Histogram Picture == the file drawing the histogram */
        ofp = fopen("HistogramPicture.txt", "w");

        int maxAppearance = OUTPUT_FILE_HEIGHT;
        for (int i = 0; i < HISTOGRAM_SIZE; ++i)
        {
            if (result[i] > maxAppearance)
            {
                maxAppearance = result[i];
            }
        }

        for (int i = maxAppearance + 1; i >= 0; --i)
        {
            for (int j = 0; j < HISTOGRAM_SIZE; ++j)
            {
                if (result[j] >= i)
                {
                    fprintf(ofp, "|");
                }

            }
            fprintf(ofp, "\n");
        }
        fclose(ofp);
    }
}


int main(int argc, char* argv[]) {

    //MPI_Init(&argc, &argv);
    read_input(argc, argv);      /* handling the input values/files */
    calculate_histogram();   /* solving the problem */
    print_output(argc, argv);     /* creating the output file with the summed up histogram */
    //MPI_Finalize();

    return 0;
}