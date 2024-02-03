#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_SIZE 5  // Replace with the desired size for the vector (N)

#define MATRIX_ROWS 5   // Replace with the desired number of rows for the matrix (N)
#define MATRIX_COLS 3   // Replace with the desired number of columns for the matrix (M)

#define LOAD_MATRIX_ROWS 5 // Define the max matrix columns of Matrix in data file.
#define LOAD_MATRIX_COLS 2 // Define the max matrix columns of Matrix in data file.

int return_message(const int err);

void load(const char* filename, double vectorNumbers[VECTOR_SIZE], double matrixNumbers[LOAD_MATRIX_ROWS][LOAD_MATRIX_COLS]);
int decomp1d(int n, int p, int myid, int *s, int *e);