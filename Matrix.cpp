#include "Matrix.h"

/*  
    ---------------------------------------
    Операторы
    ---------------------------------------
*/

std::ostream &operator<<(std::ostream &output, const Matrix &object)
{
    int i, j;
    for (i = 0; i < object.cols; i++)
    {
        for (j = 0; j < object.rows; j++)
            output << object.data[i][j] << " ";
        output << std::endl;
    }

    return output;
}

Matrix Matrix::operator+(const Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.rows != rows || right.cols != cols)
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator+()";
        exit(-4);
    }

    // Суммирование
    double **result = summarize(data, rows, cols, right.data, right.rows, right.cols, '+');

    // Возврат результата
    return Matrix(result, rows, cols);
}

Matrix Matrix::operator-(const Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.rows != rows || right.cols != cols)
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator-()";
        exit(-5);
    }

    // Суммирование
    double **result = summarize(data, rows, cols, right.data, right.rows, right.cols, '-');

    // Возврат результата
    return Matrix(result, rows, cols);
}

Matrix Matrix::operator*(const Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.rows != cols)
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator*()";
        exit(-6);
    }

    // Умножение
    double **result = multiply_matrix(data, rows, cols, right.data, right.rows, right.cols);

    // Возврат результата
    return Matrix(result, rows, cols);
}

Matrix Matrix::operator/(const Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.rows != cols)
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator/()";
        exit(-7);
    }
    if (right.rows != right.cols)
    {
        std::cerr << "Wrong matrix size in Matrix::operator/()";
        exit(-7);
    }

    Matrix invert_right = right;
    invert_right = invert_right.get_invert();

    // Умножение
    double **result = multiply_matrix(data, rows, cols, invert_right.data, invert_right.rows, invert_right.cols);

    // Освобождение памяти
    free_mem(invert_right.data, invert_right.rows);

    // Возврат результата
    return Matrix(result, rows, cols);
}

/*  
    ---------------------------------------
    Публичные функции
    ---------------------------------------
*/

Matrix Matrix::get_invert()
{
    // Проверка матрицы на квадратность
    if (cols != rows)
    {
        std::cerr << "Wrong matrix size in Matrix::get_invert()";
        exit(-1);
    }

    // Рассчёт обратного коэффициента определителя
    double d_coeff = (1 / (double)determinant(data, rows));

    // Поиск матрицы алгебраических дополнений
    double **c_matrix = cofactor(data, rows);

    // Умножение матрицы алг.доп. на обр.коэф. определителя
    double **result = multiply_number(c_matrix, rows, cols, d_coeff);

    // Очистка выделенной памяти
    free_mem(c_matrix, rows);

    // Возврат результата
    return Matrix(result, rows, cols);
}

int Matrix::get_determinant()
{
    // Проверка матрицы на квадратность
    if (cols != rows)
    {
        std::cerr << "Wrong matrix size in Matrix::get_determinant()";
        exit(-2);
    }

    // Возврат результата
    return determinant(data, rows);
}

/*  
    ---------------------------------------
    Конструкторы и деструкторы
    ---------------------------------------
*/

Matrix::Matrix(double **array, int array_rows, int array_cols)
{
    // Проверка размера матрицы
    if (array_rows < 1 || array_cols < 1)
    {
        std::cerr << "Wrong matrix size in Matrix::Matrix()";
        exit(-3);
    }

    data = array;
    rows = array_rows;
    cols = array_cols;
}

Matrix::Matrix()
{
    data = nullptr;
    rows = 0;
    cols = 0;
}

Matrix::~Matrix()
{
    free_mem(data, rows);
}

/*  
    ---------------------------------------
    Приватные функции
    ---------------------------------------
*/

int Matrix::determinant(double **matrix, int size)
{
    int d = 0, k = 1;

    if (size == 1)
    {
        d = matrix[0][0];
        return (d);
    }
    if (size == 2)
    {
        d = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
        return (d);
    }
    if (size > 2)
    {

        // Рассчёт определителя через миноры
        for (int i = 0; i < size; i++)
        {
            double **m_matrix = isolate(matrix, i, 0, size);
            d = d + k * matrix[i][0] * determinant(m_matrix, size - 1);

            // Очистка выделенной памяти
            free_mem(m_matrix, size - 1);

            k = -k;
        }
    }

    return d;
}

double **Matrix::isolate(double **matrix, int i, int j, int size)
{
    // Инициализация временного массива для миноров
    double **new_matrix;
    new_matrix = new double *[size - 1];
    for (int l = 0; l < size - 1; l++)
    {
        new_matrix[l] = new double[size - 1];
    }

    int ki, kj, di, dj;
    for (ki = 0; ki < size; ki++)
    {
        if (ki != i)
        {
            for (kj = 0; kj < size; kj++)
            {
                if (kj != j)
                {
                    if (ki > i)
                    {
                        di = 1;
                    }
                    else
                    {
                        di = 0;
                    }

                    if (kj > j)
                    {
                        dj = 1;
                    }
                    else
                    {
                        dj = 0;
                    }

                    new_matrix[ki - di][kj - dj] = matrix[ki][kj];
                }
            }
        }
    }

    return new_matrix;
}

double **Matrix::transponate(double **matrix, int size)
{
    double **new_matrix;
    new_matrix = new double *[size];
    for (int l = 0; l < size; l++)
    {
        new_matrix[l] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            new_matrix[i][j] = matrix[j][i];
        }
    }

    return new_matrix;
}

double **Matrix::multiply_number(double **matrix, int rows, int cols, double num)
{
    double **new_matrix;
    new_matrix = new double *[cols];
    for (int l = 0; l < cols; l++)
    {
        new_matrix[l] = new double[rows];
    }

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            new_matrix[i][j] = matrix[i][j] * num;
        }
    }

    return new_matrix;
}

double **Matrix::multiply_matrix(double **left, int left_r, int left_c, double **right, int right_r, int right_c)
{
    double **new_matrix;
    new_matrix = new double *[left_r];
    for (int l = 0; l < left_r; l++)
    {
        new_matrix[l] = new double[right_c];
    }

    // Вычисление результирующей матрицы
    for (int i = 0; i < left_r; i++)
    {
        for (int j = 0; j < right_c; j++)
        {
            new_matrix[i][j] = 0;
            for (int k = 0; k < left_c; k++)
            {
                new_matrix[i][j] += left[i][k] * right[k][j];
            }
        }
    }

    return new_matrix;
}

double **Matrix::summarize(double **left, int left_r, int left_c, double **right, int rigth_r, int right_c, int sign)
{
    double **new_matrix;
    new_matrix = new double *[left_r];
    for (int l = 0; l < left_r; l++)
    {
        new_matrix[l] = new double[left_c];
    }

    for (int i = 0; i < left_r; i++)
    {
        for (int j = 0; j < left_c; j++)
        {
            if (sign == '+')
            {
                new_matrix[i][j] = left[i][j] + right[i][j];
            }
            else
            {
                new_matrix[i][j] = left[i][j] - right[i][j];
            }
        }
    }

    return new_matrix;
}

double **Matrix::cofactor(double **matrix, int size)
{
    int k = 1;

    // Инициализация временного массива
    double **c_matrix;
    c_matrix = new double *[size];
    for (int l = 0; l < size; l++)
    {
        c_matrix[l] = new double[size];
    }

    // Транспонирование
    double **t_matrix = transponate(matrix, size);

    // Заполнение матрицы
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            double **m_matrix = isolate(t_matrix, i, j, size);
            int determ = determinant(m_matrix, size - 1);
            c_matrix[i][j] = k * determ;

            // Очистка выделенной памяти
            free_mem(m_matrix, size - 1);

            k = -k;
        }

        k = -k;
    }

    // Очистка выделенной памяти
    free_mem(t_matrix, size);

    // Возврат результата
    return c_matrix;
}

void Matrix::free_mem(double **array, int array_rows)
{
    for (int i = 0; i < array_rows; i++)
    {
        delete[] array[i];
    }
    delete[] array;
}