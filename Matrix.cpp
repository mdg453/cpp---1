#include <cmath>
#include <stdexcept>
#include "Matrix.h"
#include <iostream>
#define SUF 0.1
#define ERROR_INVALID_SIZE "bad size matrix for hard copy"
#define ERROR_INVALID_INPUT "bad user input "

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;
using std::swap;


Matrix::Matrix(int rows, int cols) : dims_(new (dims) {rows, cols})
                                    , matrix_(new float [rows * cols])
{

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->operator()(i,j) = 0;
        }
    }
}

Matrix::Matrix(): Matrix(1, 1) {}

Matrix::Matrix(const Matrix& m): Matrix(m.dims_->rows,m.dims_->cols)
{
    for (int i = 0; i < m.get_rows(); ++i) {
        for (int j = 0; j < m.get_cols(); ++j) {
            this->operator()(i,j) = m(i,j);
        }
    }
}

Matrix::~Matrix()
{
    delete dims_ ;
    delete[] matrix_;
}


Matrix&

Matrix::transpose ()
{
    Matrix trans_m(this->dims_->cols, this->dims_->rows) ;
    for (int i = 0; i < this->dims_->cols; i++) {
        for (int j = 0; j < this->dims_->rows; j++) {
            trans_m(i,j) = (*this)(j,i);
        }
    }
    (*this) = (trans_m) ;
    return *this ;
}

Matrix &Matrix::vectorize() {
    this->dims_->rows = this->dims_->cols*this->dims_->rows ;
    this->dims_->cols = 1 ;
    return *this ;
}

void Matrix::plain_print() const {
    for (int i = 0; i < this->dims_->rows; i++) {
        for (int j = 0; j < this->dims_->cols; j++) {
            std::cout << (*this)(i,j) << " ";
        }
        std::cout << std::endl;
    }
    printf("\n");
}

Matrix Matrix::dot(const Matrix& mat) const {
    if (this->get_cols() != mat.get_cols() || this->get_rows()
                                            != mat.get_rows()){
        throw std::domain_error(ERROR_INVALID_SIZE);
    }
    Matrix n_m(*this) ;
    for (int i = 0; i < this->get_rows()*this->get_cols(); ++i) {
        (n_m.matrix_)[i] *= mat.matrix_[i] ;
    }
    return n_m;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }
    Matrix n_m(m) ;
    swap (this->dims_->rows, n_m.dims_->rows);
    swap (this->dims_->cols, n_m.dims_->cols);
    swap (this->matrix_, n_m.matrix_);
    return (*this);
}





/* STATIC CLASS FUNCTIONS
 ********************************/



Matrix& Matrix::operator +=(const Matrix& m1)
{
    if (this->dims_->cols != m1.dims_->cols ||
            this->dims_->rows != m1.dims_->rows) {
        throw std::domain_error(ERROR_INVALID_SIZE);
    }
    for (int i = 0; i < this->dims_->rows; ++i) {
        for (int j = 0; j < this->dims_->cols; ++j) {
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

Matrix Matrix::operator*(const Matrix& m1) const {
    if (this->dims_->cols != m1.dims_->rows) {
        throw std::domain_error(ERROR_INVALID_SIZE);
    }
    Matrix c = Matrix(this->dims_->rows, m1.dims_->cols) ;
    for (int i = 0; i < this->dims_->rows; ++i) {
        for (int j =0 ; j <m1.dims_->cols; ++j) {
            for (int k = 0; k < this->dims_->cols; ++k) {
                c(i,j) += (*this)(i,k) * m1(k, j) ;
            }
        }
    }
    return c;
}


Matrix Matrix::operator*(float num) const {
    Matrix n_m = Matrix(*this);
    for (int i = 0; i < this->get_rows()* this->get_cols(); i++) {
        n_m[i] *= num ;
    }
    return n_m ;
}

Matrix operator*(float num, Matrix& m1)
{
    return m1 * num;
}


Matrix operator*(float num, const Matrix &m1) {
    return m1 * num;
}

std::istream &operator>> (std::istream &is, Matrix &matrix)
{
    if (!is.good())
    {
        throw std::runtime_error(ERROR_INVALID_INPUT);
    }
    char *buff = (char *) matrix.matrix_ ;
    if (is.good())
    {
        is.read (buff,(long)(matrix.dims_->rows * matrix.dims_->cols
                               * sizeof(float)));
    }
    return is;
}


std::ostream &operator<<(std::ostream &os, const Matrix& m) {
    for (int i = 0; i < m.dims_->rows; ++i) {
        for (int j = 0; j < m.dims_->cols; ++j) {
            if(m(i,j) > SUF){
                os << "**";
            }
            else{
                os << "  ";
            }
        }
        os << std::endl;
    }
    return os;
}

float Matrix::sum() const {
    float sumi = 0 ;
    for (int i = 0; i < dims_->cols*dims_->rows; ++i) {
        sumi += (*this)[i] ;
    }
    return sumi ;
}

double Matrix::norm() const {
    double sumi = 0 ;
    for (int i = 0; i < dims_->cols*dims_->rows; i++) {
        sumi += std::pow(((*this)[i]),2) ;
    }
    double sqrt_sum = std::sqrt(sumi) ;
    return sqrt_sum ;
}

int Matrix::argmax() const {
    int indx = 0 ;
    float biggest = 0 ;
    for (int i = 0; i < dims_->cols*dims_->rows; ++i) {
        if((*this)[i] > biggest) {
            biggest = (*this)[i] ;
            indx = i ;
        }
    }
    return indx ;
}


















