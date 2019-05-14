#include "DenseMatrix.h"
#include <vector>

using namespace std;

double DenseMatrix::get_pos(int row, int col) {
    return mat[row*n_cols + col];
}

DenseMatrix::DenseMatrix(vector<double> mat_, int cols_, int rows_) {
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