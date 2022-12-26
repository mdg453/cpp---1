/*
 * matrix.cpp
 */

#include <stdexcept>
#include "matrix.h"

#define EPS 1e-10

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

// PUBLIC MEMBER FUNCTIONS


Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = 0;
        }
    }
}

Matrix::Matrix() : rows_(1), cols_(1)
{
    allocSpace();
    matrix_[0][0] = 0;
}

Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = m.matrix_[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

Matrix Matrix::transpose()
{
    Matrix ret(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            ret.matrix_[j][i] = matrix_[i][j];
        }
    }
    return ret;
}

Matrix Matrix::vectorize() {
    int rows = rows_;
    int cols = cols_;
    Matrix vec(rows * cols, 1);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            vec.matrix_[i * cols + j][0] = matrix_[i][j];
        }
    }
    return vec;
}

void Matrix::plain_print() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    if (rows_ != m.rows_ || cols_ != m.cols_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;

        rows_ = m.rows_;
        cols_ = m.cols_;
        allocSpace();
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = m.matrix_[i][j];
        }
    }
    return *this;
}



Matrix& Matrix::operator+=(const Matrix& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] += m.matrix_[i][j];
        }
    }
    return *this;
}


Matrix& Matrix::operator*=(const Matrix& m)
{
    Matrix temp(rows_, m.cols_);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < cols_; ++k) {
                temp.matrix_[i][j] += (matrix_[i][k] * m.matrix_[k][j]);
            }
        }
    }
    return (*this = temp);
}


Matrix& Matrix::operator*=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] *= num;
        }
    }
    return *this;
}

void Matrix::swapRows(int r1, int r2)
{
    double *temp = matrix_[r1];
    matrix_[r1] = matrix_[r2];
    matrix_[r2] = temp;
}





/* STATIC CLASS FUNCTIONS
 ********************************/

Matrix Matrix::createIdentity(int size)
{
    Matrix temp(size, size);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            if (i == j) {
                temp.matrix_[i][j] = 1;
            } else {
                temp.matrix_[i][j] = 0;
            }
        }
    }
    return temp;
}

double Matrix::dotProduct(Matrix a, Matrix b)
{
    double sum = 0;
    for (int i = 0; i < a.rows_; ++i) {
        sum += (a(i, 0) * b(i, 0));
    }
    return sum;
}



/* PRIVATE HELPER FUNCTIONS
 ********************************/

void Matrix::allocSpace()
{
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_];
    }
}


Matrix Matrix::expHelper(const Matrix& m, int num)
{
    if (num == 0) {
        return createIdentity(m.rows_);
    } else if (num == 1) {
        return m;
    } else if (num % 2 == 0) {  // num is even
        return expHelper(m * m, num/2);
    } else {                    // num is odd
        return m * expHelper(m * m, (num-1)/2);
    }
}


/* NON-MEMBER FUNCTIONS
 ********************************/

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp += m2);
}


Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp *= m2);
}


Matrix operator*(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp *= num);
}


Matrix operator*(double num, const Matrix& m)
{
    return (m * num);
}


ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m.matrix_[i][0];
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m.matrix_[i][j];
        }
        os << endl;
    }
    return os;
}


istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            is >> m.matrix_[i][j];
        }
    }
    return is;
}





