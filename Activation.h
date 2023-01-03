#include "Matrix.h"
#include <iostream>
#ifndef ACTIVATION_H
#define ACTIVATION_H

namespace activation {
    Matrix relu(const Matrix& matrix_) ;
    Matrix softmax(const Matrix& matrix_) ;
    typedef Matrix (*to_activate) (const Matrix& matrix_) ;
}


#endif //ACTIVATION_H