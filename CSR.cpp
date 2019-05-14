#include "CSR.h"
#include <vector>
#include <cstdio>

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
    for(int i = 0; i < nonempty_values; i++) {
        printf("row %d col %d value %.2f\n", IA[i], JA[i], AA[i]);
    }
} 

// MISSING IMPLEMENTATION
DenseMatrix CSR::to_dense() {
    
}

CSR::CSR(int n_rows_, int n_cols_) : SparseMatrix(n_rows_, n_cols_) {
    nonempty_values = 0;
}