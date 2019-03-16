#pragma once
#include "DenseMatrix.cpp"

template <typename T>
class SparseMatrix {
    private:
        int n_rows, n_cols;        
    public:
        virtual DenseMatrix<T> to_dense()=0;
        int get_n_rows();
        int get_n_cols();
        
        SparseMatrix(int n_rows_, int n_cols_) {
            n_rows = n_rows_;
            n_cols = n_cols_;
        }
};