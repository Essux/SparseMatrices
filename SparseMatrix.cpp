#include "SparseMatrix.h"

int SparseMatrix::get_n_cols() {
    return n_cols;
}

int SparseMatrix::get_n_rows() {
    return n_rows;
}

SparseMatrix::SparseMatrix(int n_rows_, int n_cols_) {
    n_rows = n_rows_;
    n_cols = n_cols_;
}