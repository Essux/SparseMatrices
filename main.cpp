#include "COO.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int N = 3;
    vector<double> arr(N*N, 0.0);
    for (int i = 0; i < N*N; i++) {
        cin >> arr[i];
    }

    DenseMatrix a(arr, N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3.2f ", a.get_pos(i, j));
        }
        cout << '\n';
    }
    COO b = COO::from_dense(a);
    for (int i = 0; i < b.nonempty_values; i++) {
        printf("row %d col %d value %.2f\n", b.rows[i], b.cols[i], b.values[i]);
    }

    vector<double> x(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> x[i];
    }

    vector<double> ans = b.mul(x);
    for (int i = 0; i < N; i++) {
        printf("%.3f ", ans[i]);
    } printf("\n");
}