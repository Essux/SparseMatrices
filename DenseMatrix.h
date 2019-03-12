#pragma once
#include <vector>

using namespace std;

template <typename T>
class DenseMatrix {
    private:
        vector<T> mat;
        int num_of_rows, num_of_cols;        
    public:
        int get_num_of_rows();
        int get_num_of_cols();
        T get_pos(int row, int col);
        DenseMatrix(vector<T> mat_, int rows_, int cols_);
};