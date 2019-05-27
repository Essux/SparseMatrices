#include "CSC.h"
#include <vector>
#include <iostream>
#include <cmath>

CSC CSC::from_dense(DenseMatrix mat) {
  CSC repr(mat.get_n_rows(), mat.get_n_cols());

  int nnz = 0;
  repr.JA.push_back(nnz);
  
  for (int j = 0; j < mat.get_n_rows(); j++) {
    for (int i = 0; i < mat.get_n_cols(); i++) {
      double val = mat.get_pos(i, j);
      if (val != 0) {
	repr.AA.push_back(val);
	repr.IA.push_back(i);
	nnz++;
      }
    }
    repr.JA.push_back(nnz);
  }

  return repr;
}

// MISSING IMPLEMENTATION
DenseMatrix CSC::to_dense() {
  throw "not implemented";
}

void CSC::print_matrix() {
  cout << "AA: ";
  for (int i = 0; i < AA.size(); ++i) {
    cout << AA[i] << " ";
  }
  cout << endl << "IA: ";
  for (int i = 0; i < IA.size(); ++i) {
    cout << IA[i] << " ";
  }
  cout << endl << "JA: ";
  for (int i = 0; i < JA.size(); ++i) {
    cout << JA[i] << " ";
  }
  cout << endl;
}

vector<double> CSC::mul(vector<double> x) {
  vector<double> R(x.size(), 0);
  for (int i= 0, j = 0; j < AA.size(); ++j) {
    while (JA[i+1] == j) i++;
    R[IA[j]] += x[i] * AA[j];
  }
  return R;
}

CSC::CSC(int n_rows_, int n_cols_) : SparseMatrix::SparseMatrix(n_rows_, n_cols_) {}

//          i c f g a e d h b j
//IA rows = 6 2 4 5 1 3 2 5 1 6/
//JA cols = 1 2 4 5 7 9 11
