#include "COO.h"
#include <vector>
#include <cstdio>

template <typename T>
COO<T> COO<T>::from_dense(DenseMatrix<T> mat) {
    COO<T> repr;
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            T val = mat.get_pos(i, j);
            if (val!=0.0) {
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