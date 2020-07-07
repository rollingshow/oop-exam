#include <iostream>

class Matrix
{
public:
    // переменные
    double **data;
    int rows, cols;

    // операторы суммирования, вычитания, умножения и деления
    Matrix operator+(const Matrix &right);
    Matrix operator-(const Matrix &right);
    Matrix operator*(const Matrix &right);
    Matrix operator/(const Matrix &right);

    // обратная матрица
    Matrix get_invert();
    // получить определитель
    int get_determinant();

    // конструктор пустой
    Matrix();
    // конструктор с массивом из указателей, высотой и шириной
    Matrix(double **, int, int);
    // деструктор
    ~Matrix();

    // вывод матрицы
    friend std::ostream &operator<<(std::ostream &, const Matrix &);

private:
    // выборка подматрицы без столбца и строки
    double **isolate(double **, int, int, int);
    // транспонирование матрицы
    double **transponate(double **, int);
    // умножение на число
    double **multiply_number(double **, int, int, double);
    // умножение на матрицу
    double **multiply_matrix(double **, int, int, double **, int, int);
    // суммирование матриц
    double **summarize(double **, int, int, double **, int, int, int);
    // поиск матрицы алгебраических дополнений
    double **cofactor(double **, int);
    // рекурсивное вычисление определителя
    int determinant(double **, int);
    // освобождение памяти
    void free_mem(double **, int);
};