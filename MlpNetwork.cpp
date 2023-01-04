
#include "MlpNetwork.h"
using namespace activation ;
MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases)
                : r1(weights[0], biases[0], relu),
                r2(weights[1], biases[1], relu),
                r3(weights[2], biases[2], relu),
                r4(weights[3], biases[3], softmax) {}

digit MlpNetwork::operator()(const Matrix &img) const {
    Matrix temp(img);
    Matrix l1 = r1(temp.vectorize());
    Matrix l2 =r2(l1);
    Matrix l3 =r3(l2);
    Matrix l4 =r4(l3);
    int max_val = l4.argmax();
    digit dig = { (unsigned  int )max_val, l4[max_val] };
    return dig;
}



