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

vector<double> MSR::jacobi_method(vector<double> b, double tol, int maxiter) {
  int nz = AA.size();
  int nrows = b.size();
  vector<double> x(nrows, 0);
  vector<double> x0(nrows, 0);
  int k = 0;
  double err = tol + 1;
  while (err > tol and k < maxiter) {
    for (int i = 0; i < get_n_rows(); ++i) {
      x[i] = 0;
      for (int j = AJ[i]; j < AJ[i+1]; ++j) {
	x[i] += AA[j] * x0[AJ[j]];
      }
      x[i] = (b[i] - x[i]) / AA[i];
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

vector<double> MSR::successive_over_relaxation(vector<double> b, double w, double tol, int maxiter) {
  int nz = AA.size();
  int nrows = b.size();
  vector<double> x(nrows, 0);
  vector<double> x0(nrows, 0);
  int k = 0;
  double err = tol + 1;
  while (err > tol and k < maxiter) {
    for (int i = 0; i < get_n_rows(); ++i) {
      x[i] = 0;
      for (int j = AJ[i]; j < AJ[i+1]; ++j) {
        if (i < AJ[j]){
	  x[i] += AA[j] * x0[AJ[j]];
	} else {
	  x[i] += AA[j] * x[AJ[j]];
	}
      }
      x[i] = (b[i] - x[i]) / AA[i];
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


vector<double> MSR::gauss_seidel_method(vector<double> b, double tol, int maxiter) {
  return successive_over_relaxation(b, 1.0, tol, maxiter);
}

MSR::MSR(int n_rows_, int n_cols_) : SparseMatrix::SparseMatrix(n_rows_, n_cols_) {}
