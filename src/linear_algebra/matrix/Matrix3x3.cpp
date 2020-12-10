//
// Created by finne on 8/7/2020.
//

#include "Matrix3x3.h"


Matrix3x3::Matrix3x3() : DenseMatrix(3, 3) {}

Matrix3x3::Matrix3x3(Matrix3x3 &other) : DenseMatrix(3,3) {
    
    for(int i = 0; i < 3; i++){
        for(int n = 0; n < 3; n++){
            this->data[i * getN() + n] = other.get(i,n);
        }
    }
    
}



Matrix3x3::~Matrix3x3() {

}


