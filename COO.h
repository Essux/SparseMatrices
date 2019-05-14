#pragma once
#include "SparseMatrix.h"
#include "DenseMatrix.h"

class COO : public SparseMatrix {

    public:
    int nonempty_values;
    vector<double> values;
    vector<int> rows, cols;

    void add_value(double val, int row, int col);
    static COO from_dense(DenseMatrix mat);
    DenseMatrix to_dense();
    vector<double> mul(vector<double> x);

    COO(int n_rows_, int n_cols_);
};