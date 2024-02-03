#ifndef TEST_C
#define TEST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"
#include <lapacke.h>
#include <mpi.h>

#endif  // TEST_C


// // #define LOAD_MATRIX_ROWS 3;
// // #define LOAD_MATRIX_COLS 2;



int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    int np, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0){
        /* LOAD the VECTOR and MATRIX from file */
        // double vector[VECTOR_SIZE] = {1,3,2};
        printf("A = \n");
        double matrix[LOAD_MATRIX_ROWS][LOAD_MATRIX_COLS] = {
            {1, 6, 11},
            {2, 7, 12},
            {3, 8, 13},
            {4, 9, 14},
            {5, 10, 15}
        };  

        /* Print the MATRIX and the ADDRESS of ENTITIES */
        for (int i = 0; i < LOAD_MATRIX_ROWS; i++){
            for (int j = 0; j< LOAD_MATRIX_COLS; j++){
                printf("%lf -->> %p\t",matrix[i][j], &(matrix[i][j]));
            }
            printf("\n");
        }


        /* Determine the decomposition of VECTOR & MATRIX */
        /* A = 
               W0
               W1
               W2
               ...
        */
        int s, e;
        printf("\n");
        /* LOOP from PROCESS 1 to np (SEND)*/
        for (int i = 1; i < np; i++){
            /* DETERMINE the decompositions */
            decomp1d(VECTOR_SIZE, np, i, &s, &e);
            printf("Rank %d got %d members with index: [%d, %d]\n", i, e-s, s, e);


            /* Print the decompositions */
            for (int r = s; r < e; r++){
                for (int c = 0; c < LOAD_MATRIX_COLS; c++) {
                    printf("%lf -->> %p\t",matrix[r][c], &(matrix[r][c]));
                }
                printf("\n");
            }
            printf("\n");

            /* SEND the other PROCESSES */
            int N = e - s;
            MPI_Send(&N, 1, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(matrix+s, N*LOAD_MATRIX_COLS, MPI_DOUBLE, i, i+np, MPI_COMM_WORLD);
        }


        
    } else if (rank == 1) {
        
        
        /* RECV the size of MATRIXES (ROWS) and ALLOCATE MEMORIES */
        int N = 0;
        MPI_Recv(&N, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double * matrix = malloc(N*sizeof(double));
        printf("Rank %d Got %d rows \n", rank, N);
        MPI_Recv(matrix, N*LOAD_MATRIX_COLS, MPI_DOUBLE, 0, rank+np, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        /* Printing RECV MATRIXES*/
        for (int i = 0; i < N*LOAD_MATRIX_COLS; i ++){
            if (i > 0 && i%LOAD_MATRIX_COLS == 0){
                printf("\n");
            }
            printf("%.3lf ", matrix[i]);
        }


        /* DO QR Factorization on LOCAL process */
        printf("\n/*-----------------------------------------------------------*/\n\n");
        printf("QR Factorization\n\n");

        int info;
        double tau[MATRIX_COLS];
        info = LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, LOAD_MATRIX_ROWS, LOAD_MATRIX_COLS, matrix, LOAD_MATRIX_COLS, tau);
        
        /* ERROR checking */
        if (info != 0) {
            printf("QR factorization failed with error code %d\n", info);
            return 1;
        }

        /* Print the Q matrix (Note: LAPACK stores Q implicitly in the input matrix A) */
        printf("Q matrix:\n");
        for (int i = 0; i < N*LOAD_MATRIX_COLS; i ++){
            if (i > 0 && i%LOAD_MATRIX_COLS == 0){
                printf("\n");
            }
            printf("%.3lf ", matrix[i]);
        }

        printf("\nTAU: \n%lf %lf\n", tau[0], tau[1]);
        free(matrix);
    }


    MPI_Finalize();

    return 0;
}






// /**
//  * @brief This function transform the Upper-Right corner part of 
//  * input MATRIX into a VECTOR
// */
// int flatten_UR(double (*matrix)[LOAD_MATRIX_COLS], double * vector, int * count){
    
    
//     if (matrix == NULL || vector == NULL) {
//         return -1;
//     }

//     *count = 0;
//     for (int i = 0; i < LOAD_MATRIX_ROWS; i++){
//         for (int j = 0; j < LOAD_MATRIX_COLS; j++){
//             if (i <= j){
//                 vector[*count] = matrix[i][j];
//                 (*count) ++;
//             }
//         }
//     }

//     return 0;
// }


// /* TEST of MATRIX functions */
// int main(int argc, char *argv[]){

//     int np, rank;
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &np);


//     if (rank == 0){
//         printf("Rank: -->> %d\n", rank);


//         /* Suppose we have a matrix called A */
//         double A[LOAD_MATRIX_ROWS][LOAD_MATRIX_COLS];
//         printf("(double) A = \n");
//         for (int i = 0; i < LOAD_MATRIX_ROWS; i++){
//             for (int j = 0; j < LOAD_MATRIX_COLS; j++){
//                 A[i][j] = i-j+9;
//                 printf("\t%.4lf -->> %p ",A[i][j], &(A[i][j]));
//             }
//             printf("\n");
//         }

//         unsigned int R_SHAPE = (LOAD_MATRIX_COLS + 1)*(LOAD_MATRIX_COLS) / 2;
//         printf("\nSENT SHAPE %d \n", R_SHAPE);
//         size_t UNIT = sizeof(double);
//         double * MATRIX = aligned_alloc(UNIT, R_SHAPE * sizeof(double));


//         int count = 0;
//         flatten_UR(A, MATRIX, &count);

//         printf("count -->> %d\n", count);

//         for (int i = 0; i < count; i++){
//             printf("%lf -->> %p\n", MATRIX[i], MATRIX+i);
//         }

//         MPI_Send(MATRIX, count, MPI_DOUBLE, np-1, 0, MPI_COMM_WORLD);
//         MPI_Send(&count, 1, MPI_INT, np-1, 1, MPI_COMM_WORLD);
//     } 

//     if (rank == 1) {
//         printf("Rank: -->> %d\n", rank);


//         /* Suppose we have a matrix called A */
//         double A[LOAD_MATRIX_ROWS][LOAD_MATRIX_COLS] = {
//             {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}
//         };

//     //     unsigned int R_SHAPE = (LOAD_MATRIX_COLS + 1)*(LOAD_MATRIX_COLS) / 2;
//     //     printf("\nSENT SHAPE %d \n", R_SHAPE);
//     //     size_t UNIT = sizeof(double);
//     //     double * MATRIX = aligned_alloc(UNIT, R_SHAPE * sizeof(double));


//     //     int count = 0;
//     //     flatten_UR(A, MATRIX, &count);

//     //     printf("count -->> %d\n", count);

//     //     for (int i = 0; i < count; i++){
//     //         printf("%lf -->> %p\n", MATRIX[i], MATRIX+i);
//     //     }

//     //     MPI_Send(MATRIX, count, MPI_DOUBLE, np-1, 2, MPI_COMM_WORLD);
//     //     MPI_Send(&count, 1, MPI_INT, np-1, 3, MPI_COMM_WORLD);

//     }




//     MPI_Barrier(MPI_COMM_WORLD);

//     if (rank == np - 1) {
//         printf("\nRank: -->> %d\n", rank);
//         int count = 0;
//         MPI_Recv(&count, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         printf("%d\n", count);
//         double * vector = aligned_alloc(8, count * sizeof(double));
//         MPI_Recv(vector, count, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         for (int i = 0; i < count; i++){
//             printf("%lf -->> %p\n", vector[i], vector+i);
//         }


//         // int count_1 = 0;
//         // MPI_Recv(&count_1, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         // printf("%d\n", count_1);
//         // double * vector_1 = aligned_alloc(8, count_1 * sizeof(double));
//         // MPI_Recv(vector_1, count_1, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         // for (int i = 0; i < count_1; i++){
//         //     printf("%lf -->> %p\n", vector_1[i], vector_1+i);
//         // }

//     }

//     MPI_Finalize();
//     return EXIT_SUCCESS;
// }







/* Archive, Saving for loading matrix from file. */
/* ------------------------------------------------------------------------------------ */
// int main(int argc, char *argv[]) {

//     int np, rank;
//     MPI_Init(&argc, &argv);
//     MPI_Comm_size(MPI_COMM_WORLD, &np);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
//     if (rank == 0){
//         printf("ID: %d\n", rank);

//         // Check if the correct number of command-line arguments is provided
//         if (argc != 3 || strcmp(argv[1], "-f") != 0) {
//             fprintf(stderr, "Usage: %s -f filename.txt\n", argv[0]);
//             return 1; // Exit with an error code
//         }

//         // Declare arrays to store vector and matrix
//         double vector[VECTOR_SIZE];
//         double matrix[LOAD_MATRIX_ROWS][LOAD_MATRIX_COLS];


//         // Call the load function with the specified filename
//         load(argv[2], vector, matrix);

//         /*-----------------------------------------------------------*/
//         printf("\n/*-----------------------------------------------------------*/\n\n");
//         printf("LOAD DATA\n\n");
        
//         // Print the vector
//         printf("Vector:\n");
//         for (size_t i = 0; i < VECTOR_SIZE; ++i) {
//             printf("%lf ", vector[i]);
//         }
//         printf("\n\n");

//         // Print the matrix
//         printf("Matrix:\n");
//         for (size_t i = 0; i < LOAD_MATRIX_ROWS; ++i) {
//             for (size_t j = 0; j < LOAD_MATRIX_COLS; ++j) {
//                 printf("%lf -->> %p ", matrix[i][j], &(matrix[i][j]));
//             }
//             printf("\n");
//         }



//         /*-----------------------------------------------------------*/
//         printf("\n/*-----------------------------------------------------------*/\n\n");
//         printf("QR Factorization\n\n");


//         int info;
//         double tau[MATRIX_COLS];
//         info = LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, LOAD_MATRIX_ROWS, LOAD_MATRIX_COLS, *matrix, LOAD_MATRIX_COLS, tau);


//         // Check for errors
//         if (info != 0) {
//             printf("QR factorization failed with error code %d\n", info);
//             return 1;
//         }

//         // Print the Q matrix (Note: LAPACK stores Q implicitly in the input matrix A)
//         printf("Q matrix:\n");
//         for (int i = 0; i < LOAD_MATRIX_ROWS; i++) {
//             for (int j = 0; j < LOAD_MATRIX_COLS; j++) {
//                 printf("%.3lf ", matrix[i][j]);
//             }
//             printf("\n");
//         }
//         printf("\nTAU: \n%lf %lf\n", tau[0], tau[1]);
        
//         // Print the R matrix (Upper triangular factor)
//         printf("\nR matrix:\n");
//         for (int i = 0; i < LOAD_MATRIX_ROWS; i++) {
//             for (int j = 0; j < LOAD_MATRIX_COLS; j++) {
//                 if (i <= j) {
//                     printf("\t%.6lf -->> %p ", matrix[i][j], &(matrix[i][j]));
//                 } else {
//                     printf("\t0.000000 -->> %p ", &(matrix[i][j]));
//                 }
//             }
//             printf("\n");
//         }
//     } else {
//         printf("ID: %d\n", rank);
//         /*-----------------------------------------------------------*/
//         printf("\n/*-----------------------------------------------------------*/\n\n");
//     }


//     MPI_Barrier(MPI_COMM_WORLD);
//     printf("\n");
//     MPI_Barrier(MPI_COMM_WORLD);

//     /* Suppose we have vector with N elements */
//     int N = 1e5;

//     /* Determine the decomposition of vector */
//     int s, e;
//     decomp1d(N, np, rank, &s, &e);
//     printf("Rank %d got %d members with index: [%d, %d]\n", rank, e-s, s, e);

    


//     /* MPI close */
//     MPI_Finalize();

//     return 0; // Exit successfully
// }
