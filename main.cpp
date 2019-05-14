#include "COO.h"
#include "CSR.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    vector<double> arr(100, 0.0);
    for (int i = 0; i < 100; i++) {
        if (i%5==0) arr[i] = (i*0.05);
    }
    DenseMatrix a(arr, 10, 10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%3.2f ", a.get_pos(i, j));
        }
        cout << '\n';
    }
    printf("-------------------------COO-------------------------");
    COO b = COO::from_dense(a);
    for (int i = 0; i < b.nonempty_values; i++) {
        printf("row %d col %d value %.2f\n", b.rows[i], b.cols[i], b.values[i]);
    }
    printf("-------------------------CSR-------------------------");
    CSR c = CSR::from_dense(a);
    c.print_matrix();
    printf("-------------------------CSC-------------------------");
}