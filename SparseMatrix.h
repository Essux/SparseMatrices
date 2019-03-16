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
};