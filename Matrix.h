#include <iostream>
#include <vector>

class Matrix
{
public:
    // установка значений
    void set_data(int, int, double);
    void set_data(double **);
    void set_cols(int);
    void set_rows(int);
    // получение значений
    double get_data(int, int);
    double **get_data();
    int get_cols();
    int get_rows();

    // операторы суммирования, вычитания, умножения и деления
    Matrix operator+(Matrix &right);
    Matrix operator-(Matrix &right);
    Matrix operator*(Matrix &right);
    Matrix operator/(Matrix &right);

    Matrix(std::vector<double>, char);

    // обратная матрица
    Matrix get_invert();
    // получить определитель
    double get_determinant();
    // вырожденная ли матрица
    bool is_degenerate();

    // конструктор пустой
    Matrix();
    // конструктор с массивом из указателей, высотой и шириной
    Matrix(double **, int, int);

    // вывод матрицы
    friend std::ostream &operator<<(std::ostream &, Matrix &);

protected:
    // переменные
    double **data;
    int rows, cols;

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
    double determinant(double **, int);
    // освобождение памяти
    void free_mem(double **, int);
};

class Triangle_Matrix : public Matrix
{
public:
    // обработка изменений
    void set_data(int, int, double);
    void set_data(double **);

    // конструктор пустой
    Triangle_Matrix() : Matrix() {
        polarity = 'u';
    }
    // конструктор с полярностью (u - upper, l - lower)
    Triangle_Matrix(char p) : Matrix() {
        if (p != 'u' && p != 'l'){
            std::cerr << "Wrong polarity in Triangle_Matrix::Triangle_Matrix()";
            exit(-8);
        }

        polarity = p;
    }
    // конструктор с массивом из указателей, высотой, шириной и полярностью (u - upper, l - lower)
    Triangle_Matrix(double ** arr, int i, int j, char p) : Matrix(arr, i, j) {
        if (p != 'u' && p != 'l'){
            std::cerr << "Wrong polarity in Triangle_Matrix::Triangle_Matrix()";
            exit(-8);
        }
        if (i != j){
            std::cerr << "Wrong matrix size in Triangle_Matrix::Triangle_Matrix()";
            exit(-9);
        }

        polarity = p;
        triangulate();
    }
    // конструктор копирования
    Triangle_Matrix(Matrix source) : Matrix(source) {
        if (source.get_cols() != source.get_rows()){
            std::cerr << "Wrong matrix size in Triangle_Matrix::Triangle_Matrix()";
            exit(-9);
        }

        polarity = 'u';
        triangulate();
    }
    // конструктор копирования с полярностью
    Triangle_Matrix(Matrix source, char p) : Matrix(source) {
        if (p != 'u' && p != 'l'){
            std::cerr << "Wrong polarity in Triangle_Matrix::Triangle_Matrix()";
            exit(-8);
        }
        if (source.get_cols() != source.get_rows()){
            std::cerr << "Wrong matrix size in Triangle_Matrix::Triangle_Matrix()";
            exit(-9);
        }

        polarity = p;
        triangulate();
    }

private:
    char polarity;
    void triangulate();
};