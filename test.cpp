//g++ 6.3.0

#include <iostream>
#include <stdlib.h>
#include "Matrix.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // Инициализация матрицы 1
    int a_size = 4;
    double **a = new double *[a_size];
    for (int i = 0; i < a_size; i++)
    {
        a[i] = new double[a_size];
        for (int j = 0; j < a_size; j++)
        {
            a[i][j] = rand() % 4 - rand() % 3;
        }
    }
    Matrix test_matrix(a, a_size, a_size);

    // Инициализация матрицы 2
    int b_size = 4;
    double **b = new double *[b_size];
    for (int i = 0; i < b_size; i++)
    {
        b[i] = new double[b_size];
        for (int j = 0; j < b_size; j++)
        {
            b[i][j] = rand() % 6 - rand() % 8;
        }
    }
    Matrix test_matrix2(b, b_size, b_size);

    cout << "Матрица 1:" << endl << test_matrix;

    cout << "Матрица 2:" << endl << test_matrix2;

    cout << "Определитель Матрицы 1: " << test_matrix.get_determinant() << endl;

    cout << "Обратная матрица к Матрице 1:" << endl;
    Matrix invert_test_matrix = test_matrix.get_invert();
    cout << invert_test_matrix;

    cout << "Матрица 1 + Матрица 2:" << endl;
    Matrix test_matrix_sum = test_matrix + test_matrix2;
    cout << test_matrix_sum;

    cout << "Матрица 1 - Матрица 2:" << endl;
    Matrix test_matrix_sub = test_matrix - test_matrix2;
    cout << test_matrix_sub;

    cout << "Матрица 1 * Матрица 2:" << endl;
    Matrix test_matrix_mul = test_matrix * test_matrix2;
    cout << test_matrix_mul;

    cout << "Матрица 1 / Матрица 2:" << endl;
    Matrix test_matrix_div = test_matrix / test_matrix2;
    cout << test_matrix_div;

    return 0;
}
