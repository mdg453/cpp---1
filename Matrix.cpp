/*
 * matrix.cpp
 */

#include <stdexcept>
#include "Matrix.h"

#define EPS 1e-10

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

// PUBLIC MEMBER FUNCTIONS


Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    matrix_ = new float [rows_ * cols_];
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            this->matrix_[i*cols_+j] = 0;
        }
    }
}

Matrix::Matrix() : rows_(1), cols_(1)
{
    matrix_ =new float [rows_ * cols_];
    matrix_[0] = 0;
}

Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_)
{
    Matrix n_m(rows_,cols_) ;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            n_m(i,j) = m(i,j);
        }
    }
}

Matrix::~Matrix()
{
    delete[] matrix_;
}


Matrix&

Matrix::transpose ()
{
    int cols = this->get_cols() ;
    int rows = this->get_rows() ;
    Matrix trans_m(cols, rows) ;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            trans_m(i,j) = (*this)(j,i);
        }
    }
    (*this) = (trans_m) ;
}

Matrix Matrix::vectorize() {
    int cols = cols_;
    cols_ = 1 ;
    rows_ = cols*rows_ ;
    return reinterpret_cast<const Matrix &>(matrix_);
}

void Matrix::plain_print() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << matrix_[i*cols_ + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }
    Matrix n_m(m) ;
    std::swap (this->rows_, n_m.rows_);
    std::swap (this->cols_, n_m.cols_);
    std::swap (this->matrix_, n_m.matrix_);
    return (*this);
}





/* STATIC CLASS FUNCTIONS
 ********************************/



Matrix& Matrix::operator +=(const Matrix& m1)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            (*this)(i,j) += m1(i,j) ;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& m1)
{
    Matrix temp(*this) ;
    for (int i = 0; i < temp.get_cols() ; ++i) {
        for (int j = 0; j < temp.get_rows(); ++j) {
           temp(i,j) += m1(i,j) ;
        }
    }
    return (temp);
}

Matrix Matrix::operator*(const Matrix& m1)
{
    float sum = 0;
    Matrix c = Matrix(this->get_rows(), m1.cols_) ;
    for (int i = 0; i < this->get_rows(); ++i) {
        sum = 0 ;
        for (int j =0 ; j <m1.cols_; ++j) {
            for (int k = 0; k < this->cols_; ++k) {
                c(i,j) += (*this)(i,k) * m1(k, j) ;
            }
        }
    }
    return c;
}


Matrix& Matrix::operator*(float& num)
{
    Matrix temp(*this);
    for (int i = 0; i < this->get_rows()* this->get_cols(); i++) {
        this->matrix_[i] *= num ;
    }
}



//std::istream &operator>>(istream& is, Matrix& m)
//{
//    for (int i = 0; i < m.rows_; ++i) {
//        for (int j = 0; j < m.cols_; ++j) {
//            is >> m(i,j);
//        }
//    }
//    return is;
//}
//
//std::ostream &operator<<(ostream & os, const Matrix &m) {
//    for (int i = 0; i < m.rows_; ++i) {
//        os << m.matrix_[i];
//        for (int j = 1; j < m.cols_; ++j) {
//            os << " " << m(i,j);
//        }
//        os << endl;
//    }
//    return os;
//}












