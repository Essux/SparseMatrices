#include "COO.h"
#include "CSR.h"
#include "CSC.h"
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>

using namespace std;

double urand() {
    return (double) rand() / RAND_MAX;
}

void print_vector(vector<double> vec) {
    for (int i = 0; i < vec.size(); i++) printf("%.2f ", vec[i]);
    printf("\n");
}

#define MAT_TYPE COO

int main(int argc, char *argv[]) {
    int N = strtol(argv[1], NULL, 10);
    double prob = strtol(argv[2], NULL, 10)/100.0;

    srand(time(NULL));
    vector<double> arr(N*N, 0);
    for (int i = 0; i < N*N; i++) {
        if (urand()<prob) arr[i] = urand()*100;
    }
    cout << "Creados los arr" << endl;
    DenseMatrix DenseA(arr, N, N);
    MAT_TYPE A = MAT_TYPE::from_dense(DenseA);

    //A.print_matrix();

    cout << "Creadas las matrices" << endl;
    vector<double> x(N, 0);
    for (int i = 0; i < N; i++) x[i] = urand()*100;
    //print_vector(x);

    vector<double> b = A.mul(x);
    //print_vector(b);
}