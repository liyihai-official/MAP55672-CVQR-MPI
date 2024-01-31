#include <iostream>
#include <vector>
#include <lapacke.h>
#include <cblas.h>

using namespace std;

class Householder {
public:
    vector<double> v;
    int maxn;
    vector<double> H; // Add H as a member

    Householder(vector<double> v) : v(v), maxn(v.size()) {}

    vector<double> householderReflection() {
        vector<double> e1(maxn, 0.0);
        e1[0] = 1.0;

        double norm_v = cblas_dnrm2(maxn, v.data(), 1);

        if (v[0] < 0) {
            cblas_dscal(maxn, -1.0, e1.data(), 1);
        }

        vector<double> u(maxn);
        cblas_dcopy(maxn, v.data(), 1, u.data(), 1);
        cblas_daxpy(maxn, -norm_v, e1.data(), 1, u.data(), 1);
        cblas_dscal(maxn, 1.0 / cblas_dnrm2(maxn, u.data(), 1), u.data(), 1);

        H.resize(maxn * maxn, 0.0);
        for (int i = 0; i < maxn; ++i) {
            H[i * maxn + i] = 1.0;
        }

        cblas_dger(CblasRowMajor, maxn, maxn, -2.0, u.data(), 1, u.data(), 1, H.data(), maxn);

        vector<double> reflectedVector(maxn);
        cblas_dgemv(CblasRowMajor, CblasNoTrans, maxn, maxn, 1.0, H.data(), maxn, v.data(), 1, 0.0, reflectedVector.data(), 1);

        // Print Householder matrix and reflected vector if needed

        return reflectedVector;
    }
};

class QR : public Householder {
public:
    vector<vector<double>> A;
    double tol;

    QR(vector<vector<double>> A, double tol = 1e-15) : A(A), tol(tol), Householder(A[0]) {}

    void print() {
        cout << "A = " << endl;
        for (const auto &row : A) {
            for (double i : row) {
                cout << "\t" << i;
            }
            cout << endl;
        }
        cout << endl;
    }

    void appendMatrix(const vector<double>& nMatrix, vector<vector<double>>& mMatrix) {

        cout << mMatrix.size() << "\t" << nMatrix.size() << endl;
        if (nMatrix.size() > mMatrix.size()) {
            throw invalid_argument("Invalid matrix dimensions. nMatrix should have smaller or equal dimensions compared to mMatrix.");
        }

        int startRow = mMatrix.size() - nMatrix.size();
        int startCol = mMatrix[0].size() - nMatrix.size();

        for (size_t i = 0; i < nMatrix.size(); ++i) {
            for (size_t j = 0; j < nMatrix.size(); ++j) {
                mMatrix[startRow + i][startCol + j] = nMatrix[i * nMatrix.size() + j];
            }
        }
    }

    vector<vector<double>> factorization() {
        vector<vector<double>> Householders;

        while (true) {
            Householder householder(A[0]);
            auto reflectedVector = householder.householderReflection();

            vector<double> H = householder.H;
            
            A = {{0.0}};
            appendMatrix(H, A);

            Householders.push_back(H);

            if (A.empty()) {
                // Return Householders if needed
                break;
            }
        }

        return Householders;
    }
};

int main() {
    // Example usage
    vector<vector<double>> matrixA = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    QR qrDecomposition(matrixA);
    qrDecomposition.print();
    qrDecomposition.factorization();

    return 0;
}
