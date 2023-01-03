#include "Dense.h"
using namespace activation;

Dense::Dense(const Matrix &weights, const Matrix &bias,
             to_activate activation_function): weights_(weights),
                bias_(bias), activation_function_(activation_function) {};

Matrix Dense::operator()(const Matrix& input) const {
    return activation_function_((weights_ * input) + bias_) ;
}




