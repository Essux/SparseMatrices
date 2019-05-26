#pragma once
#include "DenseMatrix.h"

class SparseMatrix {
    private:
        int n_rows, n_cols;
    public:
        virtual DenseMatrix to_dense()=0;
        virtual void print_matrix()=0;
        virtual vector<double> mul(vector<double> x)=0;
        virtual vector<double> jacobi_method(vector<double> b, double tolerance, int iterations)=0;
        int get_n_rows();
        int get_n_cols();

        SparseMatrix(int n_rows_, int n_cols_);
};
