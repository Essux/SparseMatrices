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

int main() {
    int N = 3;
    vector<double> arr(N*N, 0.0);
    for (int i = 0; i < N*N; i++) {
        cin >> arr[i];
    }

    DenseMatrix a(arr, N, N);
    printf("Dense Matrix\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3.2f ", a.get_pos(i, j));
        }
        cout << '\n';
    }
    MAT_TYPE coef_mat = MAT_TYPE::from_dense(a);

    vector<double> b(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }
    try {
        printf("X Vector\n");
        vector<double> x = coef_mat.gauss_seidel_method(b, 1e-8, 40);
        print_vector(x);
    } catch (char const* e) {
        cout << e << endl;
    }
}