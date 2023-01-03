#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h" // Make sure to include the Matrix class
#include <functional> // For std::function
using activation::to_activate;
class Dense {
private:
    const Matrix weights_ ;
    const Matrix bias_ ;
    to_activate activation_function_ ;
public:
    Dense(const Matrix &weights, const Matrix &bias, activation::to_activate activation_function) ;
    Matrix get_weights() const {return weights_ ; }
    Matrix get_bias() const {return bias_ ; }
    to_activate get_activation() const {return activation_function_;}
    Matrix operator()(const Matrix& input) const ;
};


#endif //DENSE_H
