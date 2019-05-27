#include "DenseMatrix.h"
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

double DenseMatrix::get_pos(int row, int col) {
    return mat[row*n_cols + col];
}

DenseMatrix::DenseMatrix(vector<double> mat_, int rows_, int cols_) {
    n_rows = rows_;
    n_cols = cols_;
    mat.assign(n_rows * n_cols, 0);
    for(int i = 0; i < n_rows * n_cols; i++)
        mat[i] = mat_[i];
}

int DenseMatrix::get_n_cols() {
    return n_cols;
}

int DenseMatrix::get_n_rows() {
    return n_rows;
}

void DenseMatrix::print_matrix() {
    for (int i = 0; i < get_n_rows(); i++) {
        for (int j = 0; j < get_n_cols(); j++)
            printf("%3.2f ", get_pos(i, j));
        printf("\n");
    }
}

vector<double> DenseMatrix::mul(vector<double> x) {
    vector<double> b(get_n_rows(), 0);
    for (int i = 0; i < get_n_rows(); i++) {
        for (int j = 0; j < get_n_cols(); j++) {
            b[i] += get_pos(i, j) * x[j];
        }
    }
    return b;
}

vector<double> DenseMatrix::jacobi_method(vector<double> b, double tolerance, int iterations) {
    vector<double> x0 (get_n_cols(), 0);
    vector<double> x1;
    int counter = 0;
    double dispersion = tolerance+1;
    while(dispersion>tolerance && counter<iterations) {
        x1 = jacobi_iteration(x0, b);
        dispersion = measure_dispersion(x0, x1); // Uses infinite norm
        x0 = x1;
        counter++;
    }
    if (dispersion<tolerance) return x1;
    throw "Method did not converge";
}

vector<double> DenseMatrix::jacobi_iteration(vector<double> x0, vector<double> b) {
    vector<double> x1(get_n_cols(), 0);
    for (int row = 0; row < get_n_rows(); row++) {
        double sum = 0;
        if (get_pos(row, row)==0.0)
            throw "System has a 0 in the main diagonal.";

        for (int col = 0; col < get_n_cols(); col++)
            if (col!=row) sum += get_pos(row, col) * x0[col];

        x1[row] = (b[row]-sum)/get_pos(row, row);
    }
    return x1;
}


double DenseMatrix::infinite_norm(vector<double> x0) {
    double norm = 0;
    for (int i = 0; i < x0.size(); i++)
        norm = max(fabs(x0[i]), norm);
    return norm;
}

double DenseMatrix::measure_dispersion(vector<double> x0, vector<double> x1) {
    vector<double> x(x0.size(), 0);
    for (int i = 0; i < x0.size(); i++) {
        x[i] = x1[i] - x0[i];
    }
    return infinite_norm(x);
}