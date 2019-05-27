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

vector<double> CSC::jacobi_method(vector<double> b, double tol, int maxiter) {
  int nz = AA.size();
  int ncol = get_n_cols();
  vector<double> x(ncol, 0);
  vector<double> x0(ncol, 0);
  int k = 0;
  double err = tol + 1;
  vector<double> diag(ncol, 0);
  while (err > tol and k < maxiter) {
    for (int i = 0; i < ncol; ++i) {
      x[i] = 0;
    }
    for (int i = 0; i < ncol; ++i) {
      for (int j = JA[i]; j < JA[i+1]; ++j){
	if (i != IA[j]) {
	  x[IA[j]] += AA[j] * x0[i];
	} else {
	  diag[i] = AA[j];
	}
      }
    }
    for (int i = 0; i < ncol; ++i) {
      x[i] = (b[i] - x[i]) / diag[i];
    }
    err = abs(x[0] - x0[0]); //  norm(x-x0);
    for (int i = 0; i < x.size(); ++i) {
      if (abs(x[i] - x0[i]) > err) {
	err = abs(x[i] - x0[i]);
      }
    }
    double div = x[0];
    for (int i = 0; i < x.size(); ++i) {
      if (x[i] > div) {
	div = x[i];
      }
    }
    err /= div;
    x0 = x;
    k++;
  }
  if (k < maxiter) {
    return x;
  }
  throw "rip";
}

vector<double> CSC::successive_over_relaxation(vector<double> b, double w, double tol, int maxiter) {
  int nz = AA.size();
  int ncol = b.size();
  vector<double> x(ncol, 0);
  vector<double> x0(ncol, 0);
  int k = 0;
  double err = tol + 1;
  vector<double> diag(ncol, 0);
  while (err > tol and k < maxiter) {
    for (int i = 0; i < ncol; ++i) {
      x[i] = 0;
      for (int j = 0; j < JA.size()-1; ++j) {
        for (int k = JA[j]; k < JA[j+1]; ++k) {
	  if (i == IA[k]) {
	    if (i < j) {
	      x[i] += AA[k] * x0[j];
	    } else if (i > j) {
	      x[i] += AA[k] * x[j];
	    } else {
	      diag[i] = AA[k];
	    }
	  }
	}
      }
      x[i] = (b[i] - x[i]) / diag[i];
      x[i] = w*x[i] + (1-w)*x0[i];
    }
    err = abs(x[0] - x0[0]); //  norm(x-x0);
    for (int i = 0; i < x.size(); ++i) {
      if (abs(x[i] - x0[i]) > err) {
	err = abs(x[i] - x0[i]);
      }
    }
    double div = x[0];
    for (int i = 0; i < x.size(); ++i) {
      if (x[i] > div) {
	div = x[i];
      }
    }
    err /= div;
    x0 = x;
    k++;
  }
  if (k < maxiter) {
    return x;
  }
  throw "rip";
}

vector<double> CSC::gauss_seidel_method(vector<double> b, double tol, int maxiter) {
  return successive_over_relaxation(b, 1.0, tol, maxiter);
}

CSC::CSC(int n_rows_, int n_cols_) : SparseMatrix::SparseMatrix(n_rows_, n_cols_) {}
