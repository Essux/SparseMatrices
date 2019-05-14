#pragma once
#include "DenseMatrix.h"

class SparseMatrix {
    private:
        int n_rows, n_cols;
    public:
        virtual DenseMatrix to_dense()=0;
        int get_n_rows();
        int get_n_cols();

        SparseMatrix(int n_rows_, int n_cols_);

        virtual vector<double> mul(vector<double> x)=0;
};