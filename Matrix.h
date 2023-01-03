#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
using std::ostream;

class Matrix {
public:
    struct dims {
        int rows, cols;
    };
    Matrix(int rows, int cols) ;
    Matrix();
    Matrix(const Matrix& m) ;
    ~Matrix();
    Matrix &transpose();
    Matrix vectorize() ;
    void plain_print() const;
    Matrix dot(const Matrix& mat) const ;
    float * get_matrix() const { return matrix_ ; }
    int get_rows() const { return dims_->rows ; }
    int get_cols() const { return dims_->cols ; }
    float& operator()(int row, int col) { return matrix_[row*get_cols() + col]; }
    float operator()(int row, int col)  const { return matrix_[row*get_cols() + col]; }
    float& operator[](int row) { return matrix_[row]; }
    float operator[](int row) const { return matrix_[row]; }


    Matrix& operator=(const Matrix&);
    Matrix& operator+=(const Matrix& m1);
    Matrix operator+(const Matrix& m1);
    Matrix operator*(const Matrix& m1) ;
    Matrix operator*(const Matrix& m1) const ;
    Matrix & operator*(float num);
    Matrix operator*(float num) const;
    friend Matrix operator*(float num, Matrix& m1);
    friend Matrix operator*(float num, const Matrix& m1);


    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);

private:
    Matrix::dims* dims_ ;
    float *matrix_;
};


#endif
