#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

class Matrix {
private:
    int rows_, cols_;
    float *matrix_;


public:
    Matrix(int rows, int cols) ;
    Matrix();
    Matrix(const Matrix& m) ;
    ~Matrix();
    Matrix &transpose();
    Matrix vectorize() ;
    void plain_print() ;

    float * get_matrix(){ return matrix_ ; }
    int get_rows(){ return rows_ ; }
    int get_cols(){ return cols_ ; }
    float& operator()(int row, int col) { return matrix_[row*cols_ + col]; }
    float operator()(int row, int col)  const { return matrix_[row*cols_ + col]; }
    float& operator[](int row) { return matrix_[row]; }
    float operator[](int row) const { return matrix_[row]; }


    Matrix& operator=(const Matrix&);
    Matrix& operator+=(const Matrix& m1);
    Matrix operator+(const Matrix& m1);
    Matrix operator*(const Matrix& m1) ;
    Matrix & operator*(float& num);

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);

};


#endif
