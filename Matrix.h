#pragma once
#include "DenseMatrix.cpp"

template <typename T>
class Matrix {
    public:
    virtual DenseMatrix<T> to_dense()=0;
};