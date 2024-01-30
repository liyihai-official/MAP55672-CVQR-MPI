#include <iostream>
#include <cblas.h>

extern "C" {
    #include <lapacke.h>
}

int main() {
    // Define matrix sizes
    int n = 3;
    int m = 4;
    int p = 5;

    // Declare matrices
    double A[n * m] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double B[m * p] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7};
    double C[n * p];

    // Perform matrix multiplication using OpenBLAS cblas_dgemm
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, p, m, 1.0, A, m, B, p, 0.0, C, p);

    // Print the result matrix C
    std::cout << "Resultant Matrix C:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            std::cout << C[i * p + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
