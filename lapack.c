#include <stdio.h>
#include <lapacke.h>


#define N 3

int main() {
    // Input matrix A
    double A[N*N] = {
        12, -51,   4,
         6, 167, -68,
        -4,  24, -4,
    };

    // Output matrices Q and R
    double Q[N*N], R[N*N];

    // LAPACK variables
    lapack_int m = N, n = N, lda = N, lwork = -1, info;
    double work_query;

    // Computing the optimal workspace size
    dgeqrf_(&m, &n, A, &lda, NULL, &work_query, &lwork, &info);

    lwork = (lapack_int)work_query;
    double work[lwork];

    // QR factorization
    dgeqrf_(&m, &n, A, &lda, work, &work_query, &lwork, &info);

    if (info != 0) {
        printf("QR factorization failed with error code %d\n", info);
        return 1;
    }

    // Copying upper triangular part to R, and the orthogonal part to Q
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i <= j) {
                R[i * N + j] = A[i * N + j];
            }
            if (i > j) {
                Q[i * N + j] = A[i * N + j];
            }
        }
    }

    // Printing the results
    printf("Matrix Q:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.3f ", Q[i * N + j]);
        }
        printf("\n");
    }

    printf("\nMatrix R:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.3f ", R[i * N + j]);
        }
        printf("\n");
    }

    return 0;
}
