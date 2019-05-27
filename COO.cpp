#include "COO.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <map>

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

COO COO::gaussian_elimination(vector<double> b) {
    COO cur_coef = augment_matrix(b);
    for (int pivot = 0; pivot < cur_coef.get_n_rows()-1; pivot++) {
        // Map with nonzero values from the pivot column
        map<int, double> multipliers;
        bool found_diag = false;
        for (int i = 0; i < cur_coef.nonempty_values; i++) {
            if (cur_coef.cols[i]==pivot) {
                if (cur_coef.rows[i]==pivot) {
                    if (cur_coef.values[i]==0.0) throw "System has a 0 in the main diagonal.";
                    found_diag = true;
                }
                multipliers[cur_coef.rows[i]] = cur_coef.values[i];
            }
        }
        if (!found_diag) throw "System has a 0 in the main diagonal.";

        // Mantain only positions with nonzero values to construct next matrix
        map<pair<int, int>, double> fill_in;
        for (int i = 0; i < cur_coef.nonempty_values; i++) {
            // Mantain values from previous (to the pivot) rows and cols greater than pivot
            if (cur_coef.cols[i]!=pivot || cur_coef.rows[i]<=pivot) {
                pair<int, int> pair_pos = make_pair(cur_coef.rows[i], cur_coef.cols[i]);
                fill_in[pair_pos] += cur_coef.values[i];
            }
        }
        for (int i = 0; i < cur_coef.nonempty_values; i++) {
            // For every (nonzero) position of the pivot row substract the multiplier
            // to the other rows on the same column
            if (cur_coef.cols[i]>pivot && cur_coef.rows[i]==pivot) {
                for (int j = pivot+1; j<cur_coef.get_n_rows(); j++) {
                    pair<int, int> pair_pos = make_pair(j, cur_coef.cols[i]);
                    if (multipliers.count(j)) {
                        fill_in[pair_pos] -= cur_coef.values[i]*multipliers[j]/multipliers[pivot];
                    }
                }
            }
        }

        // Add the values on the map (the next nonzero values) to a new matrix
        COO next_coef(cur_coef.get_n_rows(), cur_coef.get_n_cols());
        for (map<pair<int, int>, double>::iterator it = fill_in.begin(); it!=fill_in.end(); it++) {
            int row = it->first.first;
            int col = it->first.second;
            double val = it->second;
            next_coef.add_value(val, row, col);
        }
        cur_coef = next_coef;
    }
    return cur_coef;
}

COO COO::augment_matrix(vector<double> b) {
    COO new_mat(get_n_rows(), get_n_cols()+1);
    int i = 0, j = 0;
    while (j < b.size() || i < nonempty_values) {
        while (i<nonempty_values && j==rows[i]) {
            new_mat.add_value(values[i], rows[i], cols[i]);
            i++;
        }
        while (j<b.size() && (i>=nonempty_values || j<rows[i])) {
            new_mat.add_value(b[j], j, get_n_cols());
            j++;
        }
    }
    return new_mat;
}