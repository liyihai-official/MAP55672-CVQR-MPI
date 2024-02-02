#include <stdio.h>
#include <lapacke.h>

int main() {
    // Define the matrix A
    double A[3][2] = {
        {1.0, 2.0},
        {3.0, 4.0},
        {5.0, 6.0}
    };

    // Define the dimensions of the matrix A
    int m = 3; // number of rows
    int n = 2; // number of columns

    // Define variables for LAPACK functions
    int info;
    double tau[2];

    // Perform QR factorization
    info = LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, m, n, *A, n, tau);

    // Check for errors
    if (info != 0) {
        printf("QR factorization failed with error code %d\n", info);
        return 1;
    }

    // Print the Q matrix (Note: LAPACK stores Q implicitly in the input matrix A)
    printf("Q matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\t%lf %lf\n", tau[0], tau[1]);
    // Print the R matrix (Upper triangular factor)
    printf("\nR matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                printf("%lf ", A[i][j]);
            } else {
                printf("0.0 ");
            }
        }
        printf("\n");
    }

    return 0;
}
