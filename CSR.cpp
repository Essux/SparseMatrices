#include "CSR.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

CSR CSR::from_dense(DenseMatrix mat) {
    CSR repr(mat.get_n_rows(), mat.get_n_cols());

    for(int i = 0; i < mat.get_n_rows(); i++) {
        repr.IA.push_back(repr.nonempty_values);

        for(int j = 0; j < mat.get_n_cols(); j++) {
            double val = mat.get_pos(i, j);
            if(val != (val - val)) {    
                repr.AA.push_back(val);
                repr.JA.push_back(j);
                repr.nonempty_values++;
            }
        }
    }
    repr.IA.push_back(repr.nonempty_values);
    return repr;
}

void CSR::print_matrix() {
    cout << "AA: ";
    for (int i = 0; i < AA.size(); ++i) {
        cout << AA[i] << " ";
    }
    cout << endl << "IA: ";
    for (int i = 0; i < IA.size(); ++i) {
        cout << IA[i] << " ";
    }
    cout << endl << "JA: ";
    for (int i = 0; i < JA.size(); ++i) {
        cout << JA[i] << " ";
    }
    cout << endl;
}

vector<double> CSR::mul(vector<double> x) {
    vector<double> R(x.size(), 0);
    for(int i = 0, j = 0; i < nonempty_values; i++) {
        while(IA[j + 1] == i)
            j++;
        R[j] += x[JA[i]] * AA[i];
    }
    return R;
}

// MISSING IMPLEMENTATION
DenseMatrix CSR::to_dense() {
    
}

CSR::CSR(int n_rows_, int n_cols_) : SparseMatrix(n_rows_, n_cols_) {
    nonempty_values = 0;
}

double CSR::infinity_norm_distance(vector<double> x0, vector<double> x1) {
    assert(x0.size() == x1.size());   
    double norm = 0;
    for (int i = 0; i < x0.size(); i++) {
        norm = max(norm, fabs(x0[i] - x1[i]));        
    }
    return norm;
}