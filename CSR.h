#pragma once
#include "SparseMatrix.h"

template <typename T>
class CSR : public SparseMatrix<T> {
 private:
  vector<T> values;
  vector<int> rows, cols;

 public:
  CSR<T>();
  ~CSR<T>();
}
