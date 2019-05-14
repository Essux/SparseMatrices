#pragma once
#include "SparseMatrix.h"
#include "DenseMatrix.h"

class CSR : public SparseMatrix {
    public:
    int nonempty_values;
    vector<double> AA; //Row major order
    vector<int> IA, JA;

    DenseMatrix to_dense();
    void print_matrix();
    vector<double> mul(vector<double>);

    static CSR from_dense(DenseMatrix mat);
    CSR(int n_rows_, int n_cols_);
};
    
