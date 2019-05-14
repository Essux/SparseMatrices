#include "COO.h"
#include <vector>
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

// MISSING IMPLEMENTATION
void COO::print_matrix() {
    
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