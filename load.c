#ifndef LOAD_C
#define LOAD_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"

#endif  // LOAD_C

// Function to load numbers from a file into a vector and matrix
void load(const char* filename, double vectorNumbers[VECTOR_SIZE], double matrixNumbers[LOAD_MATRIX_ROWS][LOAD_MATRIX_COLS]) {
    // Open the file
    FILE* inputFile = fopen(filename, "r");

    // Check if the file is open
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1); // Exit with an error code
    }

    // Read numbers from the file
    double num;
    size_t count = 0;
    for (size_t i = 0; i < VECTOR_SIZE + MATRIX_ROWS*MATRIX_COLS; ++i) {
        if (fscanf(inputFile, "%lf", &num) == 1) {
            if (count < VECTOR_SIZE) {
                // Store the first N numbers in the vector
                vectorNumbers[count] = num;
            } else {
                // Store the remaining numbers in the matrix
                size_t row = (i - VECTOR_SIZE) / MATRIX_COLS;
                size_t col = (i - VECTOR_SIZE) % MATRIX_COLS;

                printf("(ROW, COL) -->> num: (%ld, %ld) -->> %.2lf \n\n", row, col, num);
                if (col >= LOAD_MATRIX_COLS || row >= LOAD_MATRIX_ROWS){
                    continue;
                } else {
                    matrixNumbers[row][col] = num;
                }
            }
            ++count;
        }
    }

    // Close the file
    fclose(inputFile);

    // Check if the number of read elements matches the expected size
    if (count != VECTOR_SIZE + LOAD_MATRIX_ROWS * LOAD_MATRIX_COLS) {
        printf("count: -->> %ld\n", count);
        fprintf(stderr, "Error: Incorrect number of elements in the file.\n");
        exit(1); // Exit with an error code
    }
}