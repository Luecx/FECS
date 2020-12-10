//
// Created by finne on 7/29/2020.
//

#ifndef MATLIB_DENSEVECTOR_H
#define MATLIB_DENSEVECTOR_H


#include <ostream>

class DenseVector {
    
    private:
        double* values = nullptr;
        int size = 0;
    public:
        DenseVector();

        DenseVector(int size);
        
        DenseVector(double x, double y);
        
        DenseVector(double x, double y, double z);
        
        DenseVector(const DenseVector &other);

        DenseVector(DenseVector &&other);
        
        virtual ~DenseVector();
        
        void reset();
        
        int getSize() const;
        
        double get(int index) const;
        
        double &at(int index);
        
        void set(int index, double val);
        
        void addSelf(DenseVector& other);
        DenseVector& addNew(DenseVector& other);
        void subSelf(DenseVector& other);
        DenseVector& subNew(DenseVector& other);
        void hadamardSelf(DenseVector& other);
        DenseVector& hadamardNew(DenseVector& other);
        void scaleSelf(double scalar);
        DenseVector& scaleNew(double scalar);
        
        double dot(DenseVector& other);
        double norm(int norm);
        
        DenseVector& operator+(DenseVector& other);
        void operator+=(DenseVector& other);
        DenseVector& operator-(DenseVector& other);
        void operator-=(DenseVector& other);
        DenseVector& operator*(DenseVector& other);
        void operator*=(DenseVector& other);
        DenseVector& operator*(double other);
        void operator*=(double other);
        
        bool operator==(const DenseVector &rhs) const;
        
        bool operator!=(const DenseVector &rhs) const;
        
        double operator&(DenseVector& other);
        double operator~();
        
        double& operator()(int index);
        double operator()(int index) const;
        
        DenseVector& operator=(const DenseVector& other);
        DenseVector& operator=(DenseVector&& other);
        
        friend std::ostream &operator<<(std::ostream &os, const DenseVector &vector);
    
};


#endif //MATLIB_DENSEVECTOR_H
