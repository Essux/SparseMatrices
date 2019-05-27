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
  vector<double> jacobi_method(vector<double> b, double tol, int maxiter);
  vector<double> successive_over_relaxation(vector<double> b, double w, double tol, int maxiter);
  vector<double> gauss_seidel_method(vector<double> b, double tol, int maxiter);
  
  CSC(int n_rows_, int n_cols_);
};
