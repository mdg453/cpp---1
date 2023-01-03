#include "Activation.h"
#include <cmath>
using std::exp;
Matrix activation::relu(const Matrix& matrixa) {
    Matrix n_m(matrixa) ;
    for (int i = 0; i < n_m.get_rows()*n_m.get_cols(); ++i) {
        if (n_m[i] < 0) {
            n_m[i] = 0 ;
        }
    }
    return n_m ;
}

Matrix activation::softmax(const Matrix& matrixa) {
    Matrix n_m(matrixa) ;
    n_m.vectorize() ;
    float sum = 0 ;
    for (int i = 0; i < n_m.get_rows(); ++i) {
        float expi = exp(n_m[i]) ;
        sum += expi ;
        n_m[i] = expi ;
    }
    return (1/sum)*n_m ;
}
