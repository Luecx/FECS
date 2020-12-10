//
// Created by finn on 05.06.20.
//

#ifndef MATLIB_DENSEMATRIX_H
#define MATLIB_DENSEMATRIX_H

#include <memory.h>
#include "DenseMatrix.h"

#include <ostream>
#include "Matrix.h"
#include "cassert"

class DenseMatrix : public Matrix {
    
    
    protected:
        double *data;
    
    public:
        
        
        DenseMatrix(int mP, int nP) : Matrix(mP, nP) {
            this->data = new double[mP * nP]{0};
        }
        
        DenseMatrix(DenseMatrix &other) : Matrix(other) {
            this->data = new double[other.getM() * other.getN()]{0};
            other.copyDataTo(*this);
        }
        
        ~DenseMatrix() {
            delete this->data;
        }
        
        
        DenseMatrix &operator=(const DenseMatrix &other) {
            memcpy(this->data, other.data, m * n * sizeof(double));
            return *this;
        }
        
        DenseMatrix() = delete;
        
        int mem() override {
            return sizeof(double) * (getM() * getN()) + 2 * sizeof(int);
        }
        
        void reset() {
            memset(data, 0, m * n * sizeof(double ));
        }
        
        void set(int m, int n, double val) {
            
            
            int index = m * getN() + n;
//            assert(index < (getN() * getM()) && index >= 0);
            
            
            this->data[index] = val;
        }
        
        double &at(int m, int n) {
            int index = m * getN() + n;
            
//            assert(index < (getN() * getM()) && index >= 0);
            
            return this->data[index];
        }
        
        double get(int m, int n) const {
            
            int index = m * getN() + n;
    
//            assert(index < (getN() * getM()) && index >= 0);
            
            
            return this->data[index];
        }
        
        void copyDataTo(Matrix &other) {
            other.reset();
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    other.set(i, j, get(i, j));
                }
            }
        }
        
        void selfAdd(Matrix &other) override {
            for (int i = 0; i < getM(); i++) {
                for (int n = 0; n < getN(); n++) {
                    at(i, n) += other.get(i, n);
                }
            }
        }
        
        DenseMatrix &newAdd(Matrix &other) override {
            DenseMatrix *matrix = new DenseMatrix(*this);
            matrix->selfAdd(other);
            return *matrix;
        }
        
        DenseMatrix &newMul(Matrix &other) {
            DenseMatrix *matrix = new DenseMatrix(getM(), other.getN());
            for(int m = 0; m < getM(); m ++){
                for(int n = 0; n < other.getN(); n ++){
                    double sum = 0;
                    for(int j = 0; j < getN(); j++){
                        sum += get(m,j) * other(j,n);
                    }
                    
                    matrix->at(m,n) = sum;
                }
            }
            return *matrix;
        }
        
        DenseVector &mul(DenseVector &vec) override {
            DenseVector* out = new DenseVector(getM());
    
    
            for(int i = 0; i < getM(); i++){
        
                double sum = 0;
                for (int n = 0; n < getN(); n++) {
                    sum += vec.at(n) * get(i, n);
                }
                out->set(i,sum);
            }
    
    
            return *out;
        }
        
        inline DenseMatrix &operator+(Matrix &mat2) {
            return this->newAdd(mat2);
        }
        
        DenseMatrix& operator*(Matrix& mat){
            return this->newMul(mat);
        }
        
        DenseMatrix& operator*=(double scalar){
            for(int i = 0; i < getM(); i++){
                for (int n = 0; n < getN(); n++) {
                    at(i,n) *= scalar;
                }
            }
            return *this;
        }
        
        void selfTranspose() override {
            for(int i = 0; i < getM(); i++){
                for (int n = 0; n < i; n++) {
                    double buffer = this->get(n,i);
                    this->set(n,i,get(i,n));
                    this->set(i,n,buffer);
                }
            }
    
        }
        
        DenseMatrix &newTranspose() override {
            DenseMatrix *mat = new DenseMatrix(this->getN(), this->getM());
    
            for(int i = 0; i < getM(); i++){
        
                for (int n = 0; n < getN(); n++) {
                    mat->set(n,i,get(i,n));
                }
            }
            
            
            return *mat;
        }
        
        DenseMatrix &operator!() {
            return newTranspose();
        }
    
};


#endif //MATLIB_DENSEMATRIX_H
