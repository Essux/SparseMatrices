#include "DenseMatrix.h"
#include <vector>

using namespace std;

template <typename T>
T DenseMatrix<T>::get_pos(int row, int col) {
    return mat[row*n_cols + col];
}

template <typename T>
DenseMatrix<T>::DenseMatrix(vector<T> mat_, int cols_, int rows_) {
    n_rows = rows_;
    n_cols = cols_;
    mat.assign(n_rows * n_cols, 0);
    for(int i = 0; i < n_rows * n_cols; i++)
        mat[i] = mat_[i];
}

template <typename T>
int DenseMatrix<T>::get_n_cols() {
    return n_cols;
}

template <typename T>
int DenseMatrix<T>::get_n_rows() {
    return n_rows;
}