#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>

#define M 3
#define N 2

int main() {
    // Define the matrix A
    double A[M][N] = {
        {1.0, 2.0},
        {3.0, 4.0},
        {5.0, 6.0}
    };

    // Display the original matrix A
    printf("Original matrix A:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }

    // Perform QR factorization using LAPACK
    int min_dim = (M < N) ? M : N;
    int lda = M;
    double tau[min_dim];
    int info;

    // Call LAPACK QR factorization routine
    info = LAPACKE_dgeqr(LAPACK_COL_MAJOR, M, N, *A, lda, tau);

    if (info != 0) {
        printf("QR factorization failed with error code %d\n", info);
        exit(1);
    }

    // Display the resulting matrices Q and R
    printf("\nQR Factorization result:\n");

    // Display matrix Q
    printf("Matrix Q:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j)
                printf("1.0 ");
            else if (i > j)
                printf("0.0 ");
            else
                printf("%f ", A[i][j]);
        }
        printf("\n");
    }

    // Display matrix R
    printf("Matrix R:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (i <= j)
                printf("%f ", A[i][j]);
            else
                printf("0.0 ");
        }
        printf("\n");
    }

    return 0;
}
