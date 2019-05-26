#include "CSC.h"
#include <vector>
#include <iostream>

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

vector<double> CSC::jacobi(vector<double> b, double tol, int maxiter){
  nz = this.AA.size();
  nfil = this.n_rows;
  vector<double> x(nfil, 0);
  int k = 0;
  err = tol + 1;
  while (err > tol and k <= maxiter) {
    for (int i = 1; i < nfil; ++i) {
      x[i] = 0;
      int diag = 0;
      for (int j = this.JA[i]; j < this.JA[i+1]; ++j){
	if (i != this.IA[j]) {
	  x[i] += AA[j] * x0[i];
	} else {
	  diag = AA[j];
	}
      }
      x[i] = (b[i] - x[i]) / diag;
    }
    err = x[0] - x0[0]; // / norm(x);
    for (int i = 0; i < x.size(); ++i) {
      if (x[0] - x0[0] > err) {
	err = x[0] - x0[0];
      }
    }
    x0 = x;
    k++;
  }
  if (k < maxiter) {
    return x;
  } else {
    throw "rip";
  }
}

CSC::CSC(int n_rows_, int n_cols_) : SparseMatrix::SparseMatrix(n_rows_, n_cols_) {}

//          i c f g a e d h b j
//IA rows = 6 2 4 5 1 3 2 5 1 6/
//JA cols = 1 2 4 5 7 9 11
