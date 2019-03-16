#include "COO.h"
#include <vector>
#include <cstdio>

template <typename T>
COO<T> COO<T>::from_dense(DenseMatrix<T> mat) {
    COO<T> repr;
    repr.n_rows = mat.get_n_rows();
    repr.n_cols = mat.get_n_cols();

    for (int i = 0; i < mat.get_n_rows(); i++) {
        for (int j = 0; j < mat.get_n_cols(); j++) {
            T val = mat.get_pos(i, j);
            if (val != (val-val)) {
                repr.add_value(val, i, j);
            }
        }
    }
    return repr;
}

template <typename T>
void COO<T>::add_value(T val, int row, int col) {
    nonempty_values++;
    values.push_back(val);
    rows.push_back(row);
    cols.push_back(col);
}

// MISSING IMPLEMENTATION
template <typename T>
DenseMatrix<T> COO<T>::to_dense() {

}

template <typename T>
COO<T>::COO() {
    nonempty_values = 0;
}