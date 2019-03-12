#include "DenseMatrix.h"
#include <vector>

using namespace std;

template <typename T>
T DenseMatrix<T>::get_pos(int row, int col) {
    return mat[row*num_of_cols+col];
}

template <typename T>
DenseMatrix<T>::DenseMatrix(vector<T> mat_, int cols_, int rows_) {
    num_of_rows = rows_;
    num_of_cols = cols_;
    mat.assign(num_of_rows*num_of_cols, 0);
    for(int i = 0; i < num_of_rows*num_of_cols; i++)
        mat[i] = mat_[i];
}

template <typename T>
int DenseMatrix<T>::get_num_of_cols() {
    return num_of_cols;
}

template <typename T>
int DenseMatrix<T>::get_num_of_rows() {
    return num_of_rows;
}