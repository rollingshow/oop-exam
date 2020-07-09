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
    Triangle_Matrix t1(a, a_size, a_size, 'u');

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
    Triangle_Matrix t2(b, b_size, b_size, 'l');

    cout << "Matrix 1:" << endl
         << test_matrix;
    cout << "Triangle Matrix 1 (upper):" << endl
         << t1;

    cout << "Matrix 2:" << endl
         << test_matrix2;
    cout << "Triangle Matrix 2 (lower):" << endl
         << t2;

    cout << "Determinant of Matrix 1: " << test_matrix.get_determinant() << endl;

    cout << "Inverse matrix to Matrix 1:" << endl;
    Matrix invert_test_matrix = test_matrix.get_invert();
    cout << invert_test_matrix;

    // cout << "Matrix 1 + Matrix 2:" << endl;
    // Matrix test_matrix_sum = test_matrix + test_matrix2;
    // cout << test_matrix_sum;

    // cout << "Matrix 1 - Matrix 2:" << endl;
    // Matrix test_matrix_sub = test_matrix - test_matrix2;
    // cout << test_matrix_sub;

    cout << "Matrix 1 * Matrix 2:" << endl;
    Matrix test_matrix_mul = test_matrix * test_matrix2;
    cout << test_matrix_mul;

    // cout << "Matrix 1 / Matrix 2:" << endl;
    // Matrix test_matrix_div = test_matrix / test_matrix2;
    // cout << test_matrix_div;

    // Вводим размер слау
    int t_r = 2;
    cout << "Equations count = ";
    cin >> t_r;
    cout << "Enter SLAE values:" << endl;

    // Создаём уравнение
    double t[t_r][t_r + 1];
    for (int i = 0; i < t_r; i++)
    {
        for (int j = 0; j < t_r + 1; j++)
        {
            cout << "Equation " << i << " [" << j << "] = ";
            cin >> t[i][j];
        }
    }

    // Создаём основную матрицу
    double **t_main = new double *[t_r];
    for (int i = 0; i < t_r; i++)
    {
        t_main[i] = new double[t_r];
        for (int j = 0; j < t_r; j++)
        {
            t_main[i][j] = t[i][j];
        }
    }
    Matrix m_main(t_main, t_r, t_r);

    cout << m_main;
    // Вычисляем определитель
    double d = m_main.get_determinant();
    // Проверяем определитель
    if (d != 0)
    {

        for (int i = 0; i < t_r; i++)
        {
            Matrix m_temp(m_main);

            for (int l = 0; l < t_r; l++)
            {
                for (int k = 0; k < t_r; k++)
                {
                    if (l == i)
                    {
                        m_temp.set_data(k, i, t[k][t_r]);
                    }
                    else
                    {
                        m_temp.set_data(k, l, t[k][l]);
                    }
                }
            }
            double d_temp = m_temp.get_determinant();

            double result = d_temp / d;
            cout << "Root " << i << " = " << result << endl;
        }
    }

    return 0;
}
