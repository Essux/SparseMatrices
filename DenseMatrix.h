#pragma once
#include <vector>

using namespace std;

template <typename T>
class DenseMatrix {
    private:
        vector<T> mat;
        int n_rows, n_cols;        
    public:
        int get_n_rows();
        int get_n_cols();
        T get_pos(int row, int col);
        DenseMatrix(vector<T> mat_, int rows_, int cols_);
};