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
    // Check if the correct number of command-line arguments is provided
    if (argc != 3 || strcmp(argv[1], "-f") != 0) {
        fprintf(stderr, "Usage: %s -f filename.txt\n", argv[0]);
        return 1; // Exit with an error code
    }

    // Declare arrays to store vector and matrix
    double vector[VECTOR_SIZE];
    double matrix[MATRIX_ROWS][MATRIX_COLS];

    // Call the load function with the specified filename
    load(argv[2], vector, matrix);




    /*-----------------------------------------------------------*/
    printf("\n/*-----------------------------------------------------------*/\n\n");
    printf("LOAD FILE\n\n");
    
    // Print the vector
    printf("Vector:\n");
    for (size_t i = 0; i < VECTOR_SIZE; ++i) {
        printf("%lf ", vector[i]);
    }
    printf("\n\n");

    // Print the matrix
    printf("Matrix:\n");
    for (size_t i = 0; i < MATRIX_ROWS; ++i) {
        for (size_t j = 0; j < MATRIX_COLS; ++j) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }



    /*-----------------------------------------------------------*/
    printf("\n/*-----------------------------------------------------------*/\n\n");
    printf("QR Factorization\n\n");


    int info;
    double tau[MATRIX_COLS];
    info = LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, MATRIX_ROWS, MATRIX_COLS, *matrix, MATRIX_COLS, tau);


    // Check for errors
    if (info != 0) {
        printf("QR factorization failed with error code %d\n", info);
        return 1;
    }

    // Print the Q matrix (Note: LAPACK stores Q implicitly in the input matrix A)
    printf("Q matrix:\n");
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nTAU: \n%lf %lf\n", tau[0], tau[1]);
    // Print the R matrix (Upper triangular factor)
    printf("\nR matrix:\n");
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (i <= j) {
                printf("%lf ", matrix[i][j]);
            } else {
                printf("0.0 ");
            }
        }
        printf("\n");
    }

    

    /*-----------------------------------------------------------*/
    printf("\n/*-----------------------------------------------------------*/\n\n");



    return 0; // Exit successfully
}
