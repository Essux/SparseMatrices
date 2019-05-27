#include "COO.h"
#include "CSR.h"
#include "CSC.h"
#include "Generator.h"
#include <iostream>
#include <cstdio>

using namespace std;

void print_vector(vector<double> vec) {
    for (int i = 0; i < vec.size(); i++) printf("%.2f ", vec[i]);
    printf("\n");
}

#define MAT_TYPE COO

int main() {
    int N; cout << "Enter matrix dimension: ";
    cin >> N;

    Generator gen(0, 100);
    DenseMatrix A = gen.generate_diag_dominant(N, N, 1);
    A.print_matrix();
    vector<double> x_real = gen.generate_vector(N);
    vector<double> b = gen.generate_system(A, x_real);
    printf("Vector B\n");
    print_vector(b);

    MAT_TYPE A_sparse = MAT_TYPE::from_dense(A);

    try {
        vector<double> x_aprox = A_sparse.gauss_seidel_method(b, 1e-5, 20);
        printf("X Vector Aprox\n");
        print_vector(x_aprox);
        printf("X Vector Real\n");
        print_vector(x_real);
    } catch (char const* e) {
        cout << e << endl;
    }
}