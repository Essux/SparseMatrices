#include "Generator.h"
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cmath>

using namespace std;

// Receives the limits of the generated numbers
Generator::Generator(double a, double b) : a(a), b(b) {
    srand(time(NULL));
}

double Generator::urand(double a, double b) {
    double u = (double) rand() / RAND_MAX;
    return (b-a)*u + a;
}

DenseMatrix Generator::generate_dense(int rows, int cols, double fill_rate) {
    vector<double> vec(rows*cols, 0);
    for (int i = 0; i < rows*cols; i++)
        if (urand(0, 1)<fill_rate) vec[i] = urand(a, b);

    return DenseMatrix(vec, rows, cols);
}

// Generates a diagonally dominant matrix eg. every element in the main diagonal
// is greater than the sum of the other elements on the row
DenseMatrix Generator::generate_diag_dominant(int rows, int cols, double fill_rate) {
    DenseMatrix mat(rows, cols);
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < cols; j++) {
            if (i==j) continue;
            if (urand(0, 1)<fill_rate) {
                double val = urand(a, b);
                mat.set_pos(i, j, val);
                sum += fabs(val);
            }
        }
        // Diagonal value between 100%-120% of sum of row
        double diag_val = urand(sum, sum*1.2);
        mat.set_pos(i, i, diag_val);
    }
    return mat;
}

// Generates a band matrix. Upper_diag and lower_diag represent upper and
// lower limits of the band where 0 is the main diagonal
DenseMatrix Generator::generate_band_matrix(int rows, int cols, int upper_diag, int lower_diag) {
    DenseMatrix mat(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = max(0, i-lower_diag); j < min(cols, i+upper_diag+1); j++) {
            mat.set_pos(i, j, urand(a, b));
        }
    }
    return mat;
}

vector<double> Generator::generate_vector(int size) {
    vector<double> vec(size, 0);
    for (int i = 0; i < size; i++)
        vec[i] = urand(a, b);
    return vec;
}

// Returns vector b that satisfies Ax = b
vector<double> Generator::generate_system(DenseMatrix A, vector<double> x) {
    return A.mul(x);
}