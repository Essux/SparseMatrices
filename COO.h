#pragma once
#include "SparseMatrix.h"
#include "DenseMatrix.h"

class COO : public SparseMatrix {

    public:
    int nonempty_values;
    vector<double> values;
    vector<int> rows, cols;

    void add_value(double val, int row, int col);
    static COO from_dense(DenseMatrix mat);
    DenseMatrix to_dense();

    vector<double> mul(vector<double> x);
    COO gaussian_elimination(vector<double> b);
    vector<double> jacobi_method(vector<double> b, double tolerance, int iterations);
    vector<double> jacobi_iteration(vector<double> x0, vector<double> b);
    vector<double> gauss_seidel_method(vector<double> b, double tolerance, int iterations);
    vector<double> gauss_seidel_iteration(vector<double> x0, vector<double> b);

    COO(int n_rows_, int n_cols_);

    // Utility methods
    private:
    double infinite_norm(vector<double> x0);
    double measure_dispersion(vector<double> x0, vector<double> x1);
    void print_matrix();

};