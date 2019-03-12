#pragma once
#include "DenseMatrix.cpp"

template <typename T>
class SparseMatrix {
    private:
        int num_of_rows, num_of_cols;        
    public:
        virtual DenseMatrix<T> to_dense()=0;
        int get_num_of_rows();
        int get_num_of_cols();
};