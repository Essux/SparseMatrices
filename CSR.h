#pragma once
#include "SparseMatrix.h"
#include "DenseMatrix.h"

class CSR : public SparseMatrix
{
public:
    int nonempty_values;
    vector<double> AA; //Row major order
    vector<int> IA, JA;

    DenseMatrix to_dense();
    void print_matrix();
    static CSR from_dense(DenseMatrix mat);

    vector<double> mul(vector<double>);
    vector<double> successive_over_relaxation(vector<double> b, double relaxation_factor, double tolerance, int max_iterations);
    vector<double> gauss_seidel_method(vector<double> b, double tolerance, int max_iterations);
    vector<double> jacobi_method(vector<double> b, double tolerance, int max_iterations);

    CSR(int n_rows_, int n_cols_);

private:
    double infinity_norm_distance(vector<double> x0, vector<double> x1);
};
