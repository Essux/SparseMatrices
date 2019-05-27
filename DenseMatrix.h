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
        void print_matrix();
        double get_pos(int row, int col);
        DenseMatrix(vector<double> mat_, int rows_, int cols_);

        vector<double> mul(vector<double> x);
        vector<double> jacobi_method(vector<double> b, double tolerance, int iterations);
        vector<double> jacobi_iteration(vector<double> x0, vector<double> b);

        private:
        double infinite_norm(vector<double> x0);
        double measure_dispersion(vector<double> x0, vector<double> x1);
};