#pragma once
#include "Matrix.h"
#include "DenseMatrix.h"

template <typename T>
class COO : public Matrix<T> {

    public:
    int nonempty_values;
    vector<T> values;
    vector<int> rows, cols;
    void add_value(T val, int row, int col);
    static COO<T> from_dense(DenseMatrix<T> mat);
    DenseMatrix<T> to_dense();
    COO<T> ();
};