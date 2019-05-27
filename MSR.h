#pragma once
#include "SparseMatrix.h"
#include "DenseMatrix.h"

class MSR : public SparseMatrix {  
 public:
  vector<double> AA;
  vector<int> AJ;
  static MSR from_dense(DenseMatrix);
  DenseMatrix to_dense();
  void print_matrix();
  vector<double> mul(vector<double>);
  vector<double> jacobi_method(vector<double> b, double tol, int maxiter);
  vector<double> gauss_seidel_method(vector<double> b, double w, double tol, int maxiter);
  
  MSR(int n_rows_, int n_cols_);
};
