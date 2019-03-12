#include "SparseMatrix.h"

template<typename T>
int SparseMatrix<T>::get_num_of_cols() {
    return num_of_cols;
}

template<typename T>
int SparseMatrix<T>::get_num_of_rows() {
    return num_of_rows;
}