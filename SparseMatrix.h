#pragma once
//#include "DenseMatrix.cpp"
#include "DenseMatrix.h"

class SparseMatrix {
    private:
        int n_rows, n_cols;
    public:
        virtual DenseMatrix to_dense()=0;
        virtual void print_matrix()=0;
        int get_n_rows();
        int get_n_cols();

        SparseMatrix(int n_rows_, int n_cols_) {
            n_rows = n_rows_;
            n_cols = n_cols_;
        }
};