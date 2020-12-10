//
// Created by finn on 05.06.20.
//

#ifndef MATLIB_MATRIX_H
#define MATLIB_MATRIX_H

#include <ostream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "../vector/DenseVector.h"

class Matrix {
    
    
    protected:
        int m, n;
    
    
    public:
        
        
        Matrix(int m_p, int n_p) : m(m_p), n(n_p) {}
        
        Matrix(Matrix &other) : m(other.m), n(other.n) {}
        
        Matrix() = delete;
        
        
        virtual ~Matrix() {
        
        }
        
        
        int getM() const {
            return m;
        }
        
        int getN() const {
            return n;
        }
        
        virtual int mem() = 0;
        
        
        virtual void reset() = 0;
        
        virtual void set(int m, int n, double val) = 0;
        
        virtual double &at(int m, int n) = 0;
        
        virtual double get(int m, int n) const = 0;
        
        
        virtual void copyDataTo(Matrix &other) = 0;
        
        virtual void selfAdd(Matrix &other) = 0;
        
        virtual void selfTranspose() = 0;
        
        virtual Matrix &newTranspose() = 0;
        
        virtual Matrix &newAdd(Matrix &other) = 0;
        
        virtual DenseVector &mul(DenseVector& vec) = 0;
        
        friend void operator+=(Matrix &mat1, Matrix &mat2) {
            mat1.selfAdd(mat2);
        }
        
        virtual DenseVector& operator*(DenseVector& vec){
            return mul(vec);
        }
        
        inline double &operator()(int m, int n) {
            return at(m, n);
        }
        
        inline double operator()(int m, int n) const {
            return get(m, n);
        }
        
        friend std::ostream &operator<<(std::ostream &os, Matrix &matrix) {
            
            using std::scientific;
            using std::defaultfloat;
            using std::fixed;
            using namespace std;
            
            os << std::fixed << std::setprecision(4) << defaultfloat << std::setfill(' ');
            
            
            for (int i = 0; i < matrix.getM(); i++) {
                for (int j = 0; j < matrix.getN(); j++) {
                    os << std::setw(10) << matrix.get(i, j) << " ";
                }
                os << "\n";
            }
            return os;
        }
    
    
};


#endif //MATLIB_MATRIX_H
