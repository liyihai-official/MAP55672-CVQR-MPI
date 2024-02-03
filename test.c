#ifndef TEST_C
#define TEST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"
#include <lapacke.h>
#include <mpi.h>

#endif  // TEST_C


int main(int argc, char *argv[]) {

    int np, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    if (rank == 0){
        printf("ID: %d\n", rank);

        // Check if the correct number of command-line arguments is provided
        if (argc != 3 || strcmp(argv[1], "-f") != 0) {
            fprintf(stderr, "Usage: %s -f filename.txt\n", argv[0]);
            return 1; // Exit with an error code
        }

        // Declare arrays to store vector and matrix
        double vector[VECTOR_SIZE];
        double matrix[LOAD_MATRIX_ROWS][LOAD_MATRIX_COLS];


        // Call the load function with the specified filename
        load(argv[2], vector, matrix);

        /*-----------------------------------------------------------*/
        printf("\n/*-----------------------------------------------------------*/\n\n");
        printf("LOAD DATA\n\n");
        
        // Print the vector
        printf("Vector:\n");
        for (size_t i = 0; i < VECTOR_SIZE; ++i) {
            printf("%lf ", vector[i]);
        }
        printf("\n\n");

        // Print the matrix
        printf("Matrix:\n");
        for (size_t i = 0; i < LOAD_MATRIX_ROWS; ++i) {
            for (size_t j = 0; j < LOAD_MATRIX_COLS; ++j) {
                printf("%lf -->> %p ", matrix[i][j], &(matrix[i][j]));
            }
            printf("\n");
        }



        /*-----------------------------------------------------------*/
        printf("\n/*-----------------------------------------------------------*/\n\n");
        printf("QR Factorization\n\n");


        int info;
        double tau[MATRIX_COLS];
        info = LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, LOAD_MATRIX_ROWS, LOAD_MATRIX_COLS, *matrix, LOAD_MATRIX_COLS, tau);


        // Check for errors
        if (info != 0) {
            printf("QR factorization failed with error code %d\n", info);
            return 1;
        }

        // Print the Q matrix (Note: LAPACK stores Q implicitly in the input matrix A)
        printf("Q matrix:\n");
        for (int i = 0; i < LOAD_MATRIX_ROWS; i++) {
            for (int j = 0; j < LOAD_MATRIX_COLS; j++) {
                printf("%.3lf ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\nTAU: \n%lf %lf\n", tau[0], tau[1]);
        
        // Print the R matrix (Upper triangular factor)
        printf("\nR matrix:\n");
        for (int i = 0; i < LOAD_MATRIX_ROWS; i++) {
            for (int j = 0; j < LOAD_MATRIX_COLS; j++) {
                if (i <= j) {
                    printf("%.6lf -->> %p ", matrix[i][j], &(matrix[i][j]));
                } else {
                    printf(" 0.000000 -->> \t\t\t ");
                }
            }
            printf("\n");
        }
    } else {
        printf("ID: %d\n", rank);
        /*-----------------------------------------------------------*/
        printf("\n/*-----------------------------------------------------------*/\n\n");
    }

    
    MPI_Barrier(MPI_COMM_WORLD);

    /* Suppose we have vector with N elements */
    int N = 1e5;

    /* Determine the decomposition of vector */
    int s, e;
    decomp1d(N, np, rank, &s, &e);
    printf("Rank %d got %d members with index: [%d, %d]\n", rank, e-s, s, e);

    


    /* MPI close */
    MPI_Finalize();

    return 0; // Exit successfully
}
