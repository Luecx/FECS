//
// Created by finne on 8/7/2020.
//

#ifndef MATLIB_MATRIX3X3_H
#define MATLIB_MATRIX3X3_H


#include "Matrix.h"
#include "DenseMatrix.h"

class Matrix3x3 : public DenseMatrix {
    
    public:
        Matrix3x3();
        
        Matrix3x3(Matrix3x3 &other);
        
        virtual ~Matrix3x3();
        
        inline Matrix3x3 &operator+(Matrix3x3 &mat2) {
            return this->newAdd(mat2);
        }
        
        inline Matrix3x3 &operator*(Matrix3x3 mat) {
            return this->newMul(mat);
        }
        
        inline DenseVector &operator*(DenseVector &vec) {
            return mul(vec);
        }
        
        
        Matrix3x3 &newAdd(Matrix3x3 &other) {
            Matrix3x3 *matrix = new Matrix3x3(*this);
            matrix->selfAdd(other);
            return *matrix;
        }
        
        Matrix3x3 &newMul(Matrix3x3 &other) {
            Matrix3x3 *matrix = new Matrix3x3();
            for (int m = 0; m < getM(); m++) {
                for (int n = 0; n < other.getN(); n++) {
                    
                    
                    double sum = 0;
                    for (int j = 0; j < getN(); j++) {
                        sum += get(m, j) * other(j, n);
                    }
                    matrix->at(m, n) = sum;
                }
            }
            return *matrix;
        }
        
        
        Matrix3x3 &newTranspose() override {
            Matrix3x3 *mat = new Matrix3x3();
            
            for (int i = 0; i < getM(); i++) {
                
                for (int n = 0; n < getN(); n++) {
                    mat->set(i, n, get(n, i));
                }
            }
            
            
            return *mat;
        }
        
        Matrix3x3 &operator!() {
            return newTranspose();
        }
};


#endif //MATLIB_MATRIX3X3_H
