#pragma once
#include "SparseMatrix.h"
#include "DenseMatrix.h"

class CSC : public SparseMatrix {
 public:
  vector<double> AA;
  vector<int> IA, JA;
  static CSC from_dense(DenseMatrix);
  DenseMatrix to_dense();
  void print_matrix();
  vector<double> mul(vector<double>);
  
  CSC(int n_rows_, int n_cols_);
};
