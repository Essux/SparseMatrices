#include "MSR.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>

MSR MSR::from_dense(DenseMatrix mat) {
  MSR repr(mat.get_n_rows(), mat.get_n_cols());


  for (int i = 0; i < mat.get_n_rows(); ++i) {
    repr.AA.push_back(mat.get_pos(i, i));
  }
  repr.AA.push_back(numeric_limits<double>::infinity());
  vector<int> cols;
  for (int i = 0; i < mat.get_n_rows(); ++i) {
    repr.AJ.push_back(repr.AA.size());
    for (int j = 0; j < mat.get_n_cols(); ++j) {
      double val = mat.get_pos(i, j);
      if (i != j and val != 0) {
	repr.AA.push_back(val);
	cols.push_back(j);
      }
    }
  }
  repr.AJ.push_back(repr.AA.size());
  for (int i = 0; i < cols.size(); ++i) {
    repr.AJ.push_back(cols[i]);
  }

  return repr;
}

// MISSING IMPLEMENTATION
DenseMatrix MSR::to_dense() {
  throw "not implemented";
}

void MSR::print_matrix() {
  cout << "AA: ";
  for (int i = 0; i < AA.size(); ++i) {
    cout << AA[i] << " ";
  }
  cout << endl << "JA: ";
  for (int i = 0; i < AJ.size(); ++i) {
    cout << AJ[i] << " ";
  }
  cout << endl;
}


vector<double> MSR::mul(vector<double> x) {
  vector<double> R(x.size(), 0);
  for (int i = 0; i < x.size(); ++i) {
    R[i] += AA[i] * x[i];
    for (int j = AJ[i]; j < AJ[i+1]; ++j) {
      R[i] += AA[j] * x[AJ[j]];
    }
  }
  return R;
}

MSR::MSR(int n_rows_, int n_cols_) : SparseMatrix::SparseMatrix(n_rows_, n_cols_) {}
