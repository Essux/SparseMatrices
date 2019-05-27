#include "DenseMatrix.h"
#include <vector>
#include <cstdio>

using namespace std;

double DenseMatrix::get_pos(int row, int col) {
    return mat[row*n_cols + col];
}

DenseMatrix::DenseMatrix(vector<double> mat_, int rows_, int cols_) {
    n_rows = rows_;
    n_cols = cols_;
    mat.assign(n_rows * n_cols, 0);
    for(int i = 0; i < n_rows * n_cols; i++)
        mat[i] = mat_[i];
}

int DenseMatrix::get_n_cols() {
    return n_cols;
}

int DenseMatrix::get_n_rows() {
    return n_rows;
}

void DenseMatrix::print_matrix() {
    for (int i = 0; i < get_n_rows(); i++) {
        for (int j = 0; j < get_n_cols(); j++)
            printf("%3.2f ", get_pos(i, j));
        printf("\n");
    }
}

vector<double> DenseMatrix::mul(vector<double> x) {
    vector<double> b(get_n_rows(), 0);
    for (int i = 0; i < get_n_rows(); i++) {
        for (int j = 0; j < get_n_cols(); j++) {
            b[i] += get_pos(i, j) * x[j];
        }
    }
    return b;
}
