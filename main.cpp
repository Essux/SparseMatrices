#include "COO.h"
#include "CSR.h"
#include "CSC.h"
#include "Generator.h"
#include "MSR.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;

void print_vector(vector<double> vec) {
    for (int i = 0; i < vec.size(); i++) printf("%.2f ", vec[i]);
    printf("\n");
}

#define MAT_TYPE CSR

int main(int argc, char* argv[]) {
    ifstream file;
    file.open("matrices/bcsstk32.mtx");
    string trash;
    getline(file, trash);
    int N, M, nz;
    file >> N >> M >> nz;
    printf("N %d\n", N);

    DenseMatrix A(N, M);
    for (int i = 0; i < nz; i++) {
        int row, col;
        double val;
        file >> row >> col >> val;
        row--, col--;
        A.set_pos(row, col, val);
    }
    Generator gen(-100, 100);
    vector<double> x_theoric = gen.generate_vector(N);

    MAT_TYPE A_sparse = MAT_TYPE::from_dense(A);
    vector<double> b = A_sparse.mul(x_theoric);

    try {
        clock_t begin = clock();
        vector<double> x_real = A_sparse.gauss_seidel_method(b, 1e-9, 50);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        printf("Time: %.6f\n", elapsed_secs);
    } catch (char const* e) {
        cout << e << endl;
    }
}
