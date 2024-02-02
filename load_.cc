#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define VECTOR_SIZE 3  // Replace with the desired size for the vector (N)
#define MATRIX_ROWS 3   // Replace with the desired number of rows for the matrix (N)
#define MATRIX_COLS 3   // Replace with the desired number of columns for the matrix (M)

// Function to load numbers from a file into a vector and matrix
pair<vector<double>, vector<vector<double>>> load(const string& filename) {
    // Open the file
    ifstream inputFile(filename);

    // Check if the file is open
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1); // Exit with an error code
    }

    // Vector to store the numbers
    vector<double> vectorNumbers;

    // Matrix to store the numbers
    vector<vector<double>> matrixNumbers;

    // Read numbers from the file
    double num;
    size_t count = 0;
    while (inputFile >> num) {
        if (count < VECTOR_SIZE) {
            // Store the first N numbers in the vector
            vectorNumbers.push_back(num);
        } else {
            // Store the remaining numbers in the matrix
            if (matrixNumbers.size() < MATRIX_ROWS) {
                matrixNumbers.push_back({num});
            } else {
                matrixNumbers[matrixNumbers.size() - 1].push_back(num);
            }
        }

        ++count;
    }

    cout << "Matrix:" << endl;
    for (size_t i = 0; i < MATRIX_ROWS; ++i) {
        for (size_t j = 0; j < MATRIX_COLS; ++j) {
            cout << matrixNumbers[i][j] << "\t";
        }
        cout << endl;
    }


    // Close the file
    inputFile.close();

    // Check if the number of read elements matches the expected size
    if (vectorNumbers.size() != VECTOR_SIZE || matrixNumbers.size() != MATRIX_ROWS || matrixNumbers[0].size() != MATRIX_COLS) {
        cerr << "Error: Incorrect number of elements in the file." << endl;
        exit(1); // Exit with an error code
    }

    // Return the vector and matrix
    return {vectorNumbers, matrixNumbers};
}

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3 || string(argv[1]) != "-f") {
        cerr << "Usage: " << argv[0] << " -f filename.txt" << endl;
        return 1; // Exit with an error code
    }

    // Call the load function with the specified filename
    auto [vectorNumbers, matrixNumbers] = load(argv[2]);

    // Print the vector
    cout << "Vector: ";
    for (double i : vectorNumbers) {
        cout << i << " ";
    }
    cout << endl;

    // Print the matrix
    cout << "Matrix:" << endl;
    for (const auto &row : matrixNumbers) {
        for (double i : row) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0; // Exit successfully
}
