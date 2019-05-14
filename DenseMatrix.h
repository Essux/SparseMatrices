#pragma once
#include <vector>

using namespace std;

class DenseMatrix {
    private:
        vector<double> mat;
        int n_rows, n_cols;
    public:
        int get_n_rows();
        int get_n_cols();
        double get_pos(int row, int col);
        DenseMatrix(vector<double> mat_, int rows_, int cols_);
};