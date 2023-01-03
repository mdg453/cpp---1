
#include "MlpNetwork.h"
using namespace activation ;
MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases)
                : weights_(weights), biases_(biases) {}

digit MlpNetwork::operator()(const Matrix &img) const {
    Dense r1(this->weights_[0], this->biases_[0],
                                    relu) ;
    Matrix r1_m = r1(img) ;

    Dense r2(this->weights_[1], this->biases_[1],
                                relu) ;
    Matrix r2_m = r2(r1_m) ;

    Dense r3(this->weights_[2], this->biases_[2],
                                        relu) ;
    Matrix r3_m = r3(r2_m) ;

    Dense r4(this->weights_[3], this->biases_[3],
                                                    softmax) ;
    Matrix r4_m = r4(r3_m) ;
    digit dig;
    dig.probability = 0;
    dig.value = 0;
    for (int i = 0; i < r4_m.get_rows()*r4_m.get_cols(); ++i) {
        if (dig.probability < r4_m[i]){
            dig.probability = r4_m[i] ;
            dig.value = i ;
        }
    }
    return dig;
}



