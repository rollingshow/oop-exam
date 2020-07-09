#include "Matrix.h"

/*  
    ---------------------------------------
    Операторы
    ---------------------------------------
*/

std::ostream &operator<<(std::ostream &output, Matrix &object)
{
    int i, j;
    for (i = 0; i < object.get_cols(); i++)
    {
        for (j = 0; j < object.get_rows(); j++)
            output << object.get_data(i, j) << " ";
        output << std::endl;
    }

    return output;
}

Matrix Matrix::operator+(Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.get_rows() != get_rows() || right.get_cols() != get_cols())
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator+()";
        exit(-4);
    }

    // Суммирование
    double **result = summarize(get_data(), get_rows(), get_cols(), right.get_data(), right.get_rows(), right.get_cols(), '+');

    // Возврат результата
    return Matrix(result, get_rows(), get_cols());
}

Matrix Matrix::operator-(Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.get_rows() != get_rows() || right.get_cols() != get_cols())
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator-()";
        exit(-5);
    }

    // Суммирование
    double **result = summarize(get_data(), get_rows(), get_cols(), right.get_data(), right.get_rows(), right.get_cols(), '-');

    // Возврат результата
    return Matrix(result, get_rows(), get_cols());
}

Matrix Matrix::operator*(Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.get_rows() != get_cols())
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator*()";
        exit(-6);
    }

    // Умножение
    double **result = multiply_matrix(get_data(), get_rows(), get_cols(), right.get_data(), right.get_rows(), right.get_cols());

    // Возврат результата
    return Matrix(result, get_rows(), get_cols());
}

Matrix Matrix::operator/(Matrix &right)
{
    // Проверка матриц на соответствие размеров
    if (right.get_rows() != get_cols())
    {
        std::cerr << "Unequal matrix sizes in Matrix::operator/()";
        exit(-7);
    }
    if (right.get_rows() != right.get_cols())
    {
        std::cerr << "Wrong matrix size in Matrix::operator/()";
        exit(-7);
    }

    Matrix invert_right = right;
    invert_right = invert_right.get_invert();

    // Умножение
    double **result = multiply_matrix(get_data(), get_rows(), get_cols(), invert_right.get_data(), invert_right.get_rows(), invert_right.get_cols());

    // Освобождение памяти
    free_mem(invert_right.get_data(), invert_right.get_rows());

    // Возврат результата
    return Matrix(result, get_rows(), get_cols());
}

/*  
    ---------------------------------------
    Публичные функции
    ---------------------------------------
*/

Matrix Matrix::get_invert()
{
    // Проверка матрицы на квадратность
    if (get_cols() != get_rows())
    {
        std::cerr << "Wrong matrix size in Matrix::get_invert()";
        exit(-1);
    }

    // Рассчёт обратного коэффициента определителя
    double d_coeff = (1 / (double)determinant(get_data(), get_rows()));

    // Поиск матрицы алгебраических дополнений
    double **c_matrix = cofactor(get_data(), get_rows());

    // Умножение матрицы алг.доп. на обр.коэф. определителя
    double **result = multiply_number(c_matrix, get_rows(), get_cols(), d_coeff);

    // Очистка выделенной памяти
    free_mem(c_matrix, get_rows());

    // Возврат результата
    return Matrix(result, get_rows(), get_cols());
}

double Matrix::get_determinant()
{
    // Проверка матрицы на квадратность
    if (get_cols() != get_rows())
    {
        std::cerr << "Wrong matrix size in Matrix::get_determinant()";
        exit(-2);
    }

    // Возврат результата
    return determinant(get_data(), get_rows());
}

bool Matrix::is_degenerate()
{
    if (get_determinant() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*  
    ---------------------------------------
    Конструкторы
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

    double **temp = new double *[array_rows];
    for (int i = 0; i < array_rows; i++)
    {
        temp[i] = new double[array_cols];
        for (int j = 0; j < array_cols; j++)
        {
            temp[i][j] = array[i][j];
        }
    }

    set_data(temp);
    set_rows(array_rows);
    set_cols(array_cols);
}

Matrix::Matrix()
{
    set_data(nullptr);
    set_rows(0);
    set_cols(0);
}

// Matrix::Matrix(const Matrix &source)
// {
    // double **temp = new double *[source.get_rows()];
    // for (int i = 0; i < source.get_rows(); i++)
    // {
    //     temp[i] = new double[source.get_cols()];
    //     for (int j = 0; j < source.get_cols(); j++)
    //     {
    //         temp[i][j] = source.get_data(i, j);
    //     }
    // }

//     int temp_r = source.get_rows(), temp_c = source.get_cols();  

//     set_data(temp);
//     set_rows(temp_r);
//     set_cols(temp_c);
// }

/*  
    ---------------------------------------
    Приватные функции
    ---------------------------------------
*/

double Matrix::determinant(double **matrix, int size)
{
    double d = 0;
    int k = 1;

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

double **Matrix::multiply_number(double **matrix, int r, int c, double num)
{
    double **new_matrix;
    new_matrix = new double *[c];
    for (int l = 0; l < c; l++)
    {
        new_matrix[l] = new double[r];
    }

    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
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
            double determ = determinant(m_matrix, size - 1);
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

/*  
    ---------------------------------------
    Сеттеры и геттеры
    ---------------------------------------
*/

void Matrix::set_data(int i, int j, double value)
{
    if (i < get_rows() && i >= 0 && j < get_cols() && j >= 0)
    {
        data[i][j] = value;
    }
    else
    {
        std::cerr << "Wrong position in Matrix::set_data()";
        return;
    }
}

void Matrix::set_data(double **array)
{
    data = array;
}

void Matrix::set_cols(int c)
{
    cols = c;
}

void Matrix::set_rows(int r)
{
    rows = r;
}

double Matrix::get_data(int i, int j)
{
    if (i < get_rows() && i >= 0 && j < get_cols() && j >= 0)
    {
        return data[i][j];
    }
    else
    {
        std::cerr << "Wrong position in Matrix::get_data()";
        return 0;
    }
}

double **Matrix::get_data()
{
    return data;
}

int Matrix::get_cols()
{
    return cols;
}

int Matrix::get_rows()
{
    return rows;
}

/*  
    ---------------------------------------
    Треугольная матрица
    ---------------------------------------
*/

void Triangle_Matrix::set_data(int i, int j, double value){
    this->Matrix::set_data(i, j, value);
    triangulate();
}

void Triangle_Matrix::set_data(double** array){
    this->Matrix::set_data(array);
    triangulate();
}

void Triangle_Matrix::triangulate(){
    if (get_cols() != get_rows())
    {
        std::cerr << "Wrong matrix size in Triangle_Matrix::triangulate()";
        exit(-9);
    }

    for (int i = 0; i < get_rows(); i++){
        for (int j = 0; j < get_rows(); j++){
            if(polarity == 'u'){
                if (j < i){
                    this->Matrix::data[i][j] = 0.0;
                }
            } else {
                if (j > i){
                    this->Matrix::data[i][j] = 0.0;
                }
            }
        }
    }
}
