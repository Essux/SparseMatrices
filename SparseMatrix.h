#pragma once
#include "DenseMatrix.cpp"

template <typename T>
class SparseMatrix {
    public:
    virtual DenseMatrix<T> to_dense()=0;
};