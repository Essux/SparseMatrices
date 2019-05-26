#include "COO.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>

COO COO::from_dense(DenseMatrix mat) {
    COO repr(mat.get_n_rows(), mat.get_n_cols());

    for (int i = 0; i < mat.get_n_rows(); i++) {
        for (int j = 0; j < mat.get_n_cols(); j++) {
            double val = mat.get_pos(i, j);
            if (val != (val-val)) {
                repr.add_value(val, i, j);
            }
        }
    }
    return repr;
}

void COO::add_value(double val, int row, int col) {
    nonempty_values++;
    values.push_back(val);
    rows.push_back(row);
    cols.push_back(col);
}

// MISSING IMPLEMENTATION
DenseMatrix COO::to_dense() {
    throw "not implemented";
}

void COO::print_matrix() {
  cout << "AA: ";
  for (int i = 0; i < nonempty_values; ++i) {
    cout << values[i] << " ";
  }
  cout << endl << "IA: ";
  for (int i = 0; i < nonempty_values; ++i) {
    cout << rows[i] << " ";
  }
  cout << endl << "JA: ";
  for (int i = 0; i < nonempty_values; ++i) {
    cout << cols[i] << " ";
  }
  cout << endl;
}

COO::COO(int n_rows_, int n_cols_) : SparseMatrix::SparseMatrix(n_rows_, n_cols_) {
    nonempty_values = 0;
}

vector<double> COO::mul(vector<double> x){
    vector<double> b(x.size(), 0);
    for (int i = 0; i < nonempty_values; i++) {
        b[rows[i]] += x[cols[i]] * values[i];
    }
    return b;
}

vector<double> COO::jacobi_method(vector<double> b, double tolerance, int iterations) {
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

vector<double> COO::jacobi_iteration(vector<double> x0, vector<double> b) {
    vector<double> x1(get_n_cols(), 0);
    for (int row = 0; row < get_n_rows(); row++) {
        double sum = 0;
        double diag = 0; // Value of the diagonal
        for (int i = 0; i < nonempty_values; i++) {
            if (rows[i]==row) {
                if (cols[i]==row) diag = values[i];
                else sum += values[i]*x0[cols[i]];
            }
        }
        if (diag==0.0) throw "System has a 0 in the main diagonal.";
        x1[row] = (b[row]-sum)/diag;
    }
    return x1;
}

vector<double> COO::gauss_seidel_method(vector<double> b, double tolerance, int iterations) {
    vector<double> x0 (get_n_cols(), 0);
    vector<double> x1;
    int counter = 0;
    double dispersion = tolerance+1;
    while(dispersion>tolerance && counter<iterations) {
        x1 = gauss_seidel_iteration(x0, b);
        dispersion = measure_dispersion(x0, x1); // Uses infinite norm
        x0 = x1;
        counter++;
    }
    if (dispersion<tolerance) return x1;
    throw "Method did not converge";
}

vector<double> COO::gauss_seidel_iteration(vector<double> x0, vector<double> b) {
    vector<double> x1(get_n_cols(), 0);
    for (int i = 0; i < get_n_cols(); i++) x1[i] = x0[i];

    for (int row = 0; row < get_n_rows(); row++) {
        double sum = 0;
        double diag = 0; // Value of the diagonal
        for (int i = 0; i < nonempty_values; i++) {
            if (rows[i]==row) {
                if (cols[i]==row) diag = values[i];
                else sum += values[i]*x1[cols[i]];
            }
        }
        if (diag==0.0) throw "System has a 0 in the main diagonal.";
        x1[row] = (b[row]-sum)/diag;
    }
    return x1;
}

double COO::infinite_norm(vector<double> x0) {
    double norm = 0;
    for (int i = 0; i < x0.size(); i++)
        norm = max(fabs(x0[i]), norm);
    return norm;
}

double COO::measure_dispersion(vector<double> x0, vector<double> x1) {
    vector<double> x(x0.size(), 0);
    for (int i = 0; i < x0.size(); i++) {
        x[i] = x1[i] - x0[i];
    }
    return infinite_norm(x);
}
