#include "DenseMatrix.h"
#include <vector>

using namespace std;

template <typename T>
T DenseMatrix<T>::get_pos(int row, int col) {
    return mat[row*cols+col];
}

template <typename T>
DenseMatrix<T>::DenseMatrix(vector<T> mat_, int cols_, int rows_) {
    rows = rows_;
    cols = cols_;
    mat.assign(rows*cols, 0);
    for(int i = 0; i < rows*cols; i++)
        mat[i] = mat_[i];
}