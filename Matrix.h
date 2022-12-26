/*
 * matrix.h
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

class Matrix {
private:
    int rows_, cols_;
    double **matrix_;

    void allocSpace();
    Matrix expHelper(const Matrix&, int);


public:
    Matrix(int, int);
    Matrix();


    ~Matrix();
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix&);

    int get_rows(){
        return rows_ ;
    }
    int get_cols(){
        return cols_ ;
    }
    Matrix transpose();

    Matrix vectorize() ;

    void plain_print() ;


    inline double& operator()(int x, int y) { return matrix_[x][y]; }
    double* operator[](int row) { return matrix_[row * cols_]; }

    Matrix& operator+=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(double);

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);

    void swapRows(int, int);


    static Matrix createIdentity(int);


    // functions on vectors
    static double dotProduct(Matrix, Matrix);

};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator/(const Matrix&, double);

#endif
