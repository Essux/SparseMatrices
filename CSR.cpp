#include "CSR.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>


CSR CSR::from_dense(DenseMatrix mat)
{
    CSR repr(mat.get_n_rows(), mat.get_n_cols());

    for (int i = 0; i < mat.get_n_rows(); i++)
    {
        repr.IA.push_back(repr.nonempty_values);

        for (int j = 0; j < mat.get_n_cols(); j++)
        {
            double val = mat.get_pos(i, j);

            if (val != (val - val))
            {
                repr.AA.push_back(val);
                repr.JA.push_back(j);
                repr.nonempty_values++;
            }
        }
    }
    repr.IA.push_back(repr.nonempty_values);
    return repr;
}

void CSR::print_matrix()
{
    cout << "AA: ";
    for (int i = 0; i < AA.size(); ++i)
    {
        cout << AA[i] << " ";
    }
    cout << endl
         << "IA: ";
    for (int i = 0; i < IA.size(); ++i)
    {
        cout << IA[i] << " ";
    }
    cout << endl
         << "JA: ";
    for (int i = 0; i < JA.size(); ++i)
    {
        cout << JA[i] << " ";
    }
    cout << endl;
}


vector<double> CSR::mul(vector<double> x)
{
    vector<double> R(x.size(), 0);
    for (int i = 0, j = 0; i < nonempty_values; i++)
    {
        while (IA[j + 1] == i)
            j++;
        R[j] += x[JA[i]] * AA[i];
    }
    return R;
}

// MISSING IMPLEMENTATION
DenseMatrix CSR::to_dense()
{}


CSR::CSR(int n_rows_, int n_cols_) : SparseMatrix(n_rows_, n_cols_)
{
    nonempty_values = 0;
}

vector<double> CSR::successive_over_relaxation(
    vector<double> b, double relaxation_factor, double tolerance,
    int max_iterations)
{
    if (get_n_cols() != get_n_cols() || get_n_rows() != b.size())
        throw "System must be square.";

    int nz = AA.size();
    int nfil = get_n_rows();
    int it_counter = 0;
    double dispersion = tolerance + 1;

    vector<double> x0(nfil, 0);
    vector<double> x(nfil, 0);
    while (dispersion > tolerance && it_counter <= max_iterations)
    {
        for (int i = 0; i < nfil; i++)
        {
            double diag = 0;
            x[i] = 0;
            for (int j = IA[i]; j <= IA[i + 1] - 1; j++)
            {
                if (i < JA[j])
                    x[i] += AA[j] * x0[JA[j]];
                else if (i > JA[j])
                    x[i] += AA[j] * x[JA[j]];
                else
                    diag = AA[j];
            }
            if (diag == 0)
                throw "System has a 0 in the main diagonal.";
            x[i] = (b[i] - x[i]) / diag;
            x[i] = relaxation_factor * x[i] +
                   (1.0 - relaxation_factor) * x0[i];
        }
        dispersion = infinity_norm_distance(x, x0);
        for (int i = 0; i < nfil; i++)
            x0[i] = x[i];
        it_counter++;
    }
    if (dispersion < tolerance)
        return x;
    else
        throw "Method did not converge.";
}

vector<double> CSR::gauss_seidel_method(vector<double> b, double tolerance, int max_iterations)
{
    return successive_over_relaxation(b, 1.0, tolerance, max_iterations);
}

vector<double> CSR::jacobi_method(vector<double> b, double tolerance, int max_iterations)
{
    if (get_n_cols() != get_n_cols() || get_n_rows() != b.size())
        throw "System must be square.";

    int nz = AA.size();
    int nfil = get_n_rows();
    int it_counter = 0;
    double dispersion = tolerance + 1;

    vector<double> x0(nfil, 0);
    vector<double> x(nfil, 0);
    while (dispersion > tolerance && it_counter <= max_iterations)
    {
        for (int i = 0; i < nfil; i++)
        {
            double diag = 0;
            x[i] = 0;
            for (int j = IA[i]; j <= IA[i + 1] - 1; j++)
            {
                if (i != JA[j])
                    x[i] += AA[j] * x0[JA[j]];
                else
                    diag = AA[j];
            }
            if (diag == 0)
                throw "System has a 0 in the main diagonal.";
            x[i] = (b[i] - x[i]) / diag;
        }
        dispersion = infinity_norm_distance(x, x0);
        for (int i = 0; i < nfil; i++)
            x0[i] = x[i];
        it_counter++;
    }
    if (dispersion < tolerance)
        return x;
    else
        throw "Method did not converge.";
}

double CSR::infinity_norm_distance(vector<double> x0, vector<double> x1)
{
    assert(x0.size() == x1.size());
    double norm = 0;
    for (int i = 0; i < x0.size(); i++)
    {
        norm = max(norm, fabs(x0[i] - x1[i]));
    }
    return norm;
}
