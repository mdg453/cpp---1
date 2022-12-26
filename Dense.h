//#ifndef DENSE_H
//#define DENSE_H
//
//#include "Activation.h"
//
//#include "matrix.h" // Make sure to include the Matrix class
//#include <functional> // For std::function
//typedef Matrix (*ActivationFunction)(const Matrix&);
//
//class Dense {
//public:
//    // Constructor that takes in two matrices and an activation function
//    Dense(const Matrix& weights, const Matrix& bias, std::function<int(int)> activation)
//            : weights_(weights), bias_(bias), activation_(activation) {}
//
//    // Parenthesis operator overload that applies the layer to the input matrix and returns the output matrix
//    Matrix operator()(const Matrix& input) {
//        Matrix output = weights_ * input + bias_; // Calculate the output matrix
//        for (int i = 0; i < output.rows(); i++) {
//            for (int j = 0; j < output.cols(); j++) {
//                output(i, j) = activation_(output(i, j)); // Apply the activation function element-wise
//            }
//        }
//        return output;
//    }
//    Matrix get_weights() const {
//        return weights_;
//    }
//    Matrix get_bias() const {
//        return bias_;
//    }
//    ActivationFunction get_activation() const {
//        return activation_;
//    }
//
//private:
//    Matrix weights_; // Weights matrix
//    Matrix bias_; // Bias matrix
//    std::function<int(int)> activation_; // Activation function
//};
//
//
//#endif //DENSE_H
