#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_SIZE 3  // Replace with the desired size for the vector (N)
#define MATRIX_ROWS 3   // Replace with the desired number of rows for the matrix (N)
#define MATRIX_COLS 3   // Replace with the desired number of columns for the matrix (M)

void load(const char* filename, double vectorNumbers[VECTOR_SIZE], double matrixNumbers[MATRIX_ROWS][MATRIX_COLS]);
