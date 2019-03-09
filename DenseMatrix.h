#pragma once
#include <vector>

using namespace std;

template <typename T>
class DenseMatrix {
    private:
    vector<T> mat;

    public:
    int rows, cols;
    T get_pos(int row, int col);
    DenseMatrix(vector<T> mat_, int rows_, int cols_);
};