#pragma once
#include "DenseMatrix.h"

using namespace std;

class Generator {
    public:
    Generator(double a, double b);
    DenseMatrix generate_dense(int rows, int cols, double fill_rate);
    DenseMatrix generate_diag_dominant(int rows, int cols, double fill_rate);
    vector<double> generate_vector(int size);
    vector<double> generate_system(DenseMatrix A, vector<double> x);

    private:
    double a, b;
    double urand(double a, double b);
};