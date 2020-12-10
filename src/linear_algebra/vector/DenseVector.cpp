//
// Created by finne on 7/29/2020.
//

#include <cstring>
#include <cmath>
#include "DenseVector.h"
#include <immintrin.h>
#include <iostream>

DenseVector::DenseVector() : DenseVector(3) {

}

DenseVector::DenseVector(int size) : size(size) {
//    this->values = new (std::align_val_t(32)) double [size]{0};
    this->values = new double[size + size % 2]{0};
}

DenseVector::DenseVector(double x, double y) {
    this->size = 2;
    this->values = new double[2]{x,y};
}

DenseVector::DenseVector(double x, double y, double z) {
    this->size = 3;
    this->values = new double[4]{x,y,z};
}

DenseVector::DenseVector(const DenseVector &other) : size(other.size) {
//    this->values = new (std::align_val_t(32)) double [size]{0};
    this->values = new double[size + size % 2]{0};
    memcpy(values, other.values, size * sizeof(double));
}

DenseVector::DenseVector(DenseVector &&other) : values(other.values), size(other.size){
    other.values = nullptr;
}


DenseVector::~DenseVector() {
//    _mm_free(values);
    if(values != nullptr){
        delete[] values;
        values = nullptr;
    }
}

void DenseVector::reset() {
    memset(values, 0, sizeof(double) * size);
}

int DenseVector::getSize() const {
    return size;
}

double DenseVector::get(int index) const {
    return values[index];
}

double &DenseVector::at(int index) {
    return values[index];
}

void DenseVector::set(int index, double val) {
    values[index] = val;
}

void DenseVector::addSelf(DenseVector &other) {
    
    for(int i = 0; i < size; i+=2){
        
        _mm_store_pd(&values[i],
                _mm_add_pd(
                        _mm_load_pd(&values[i]),
                        _mm_load_pd(&other.values[i])));
        
    }
    
//    for (int i = 0; i < size; i++) {
//
//
//
//        this->values[i] += other(i);
//    }
}

DenseVector &DenseVector::addNew(DenseVector &other) {
    DenseVector *vec = new DenseVector(*this);
    vec->addSelf(other);
    return *vec;
}

void DenseVector::subSelf(DenseVector &other) {
    
    for(int i = 0; i < size; i+=2){
        
        _mm_store_pd(&values[i],
                     _mm_sub_pd(
                             _mm_load_pd(&values[i]),
                             _mm_load_pd(&other.values[i])));
        
    }
    
//    for (int i = 0; i < size; i++) {
//        this->values[i] -= other(i);
//    }
}

DenseVector &DenseVector::subNew(DenseVector &other) {
    DenseVector *vec = new DenseVector(*this);
    vec->subSelf(other);
    return *vec;
}

void DenseVector::hadamardSelf(DenseVector &other) {
    
    for(int i = 0; i < size; i+=2){
        
        _mm_store_pd(&values[i],
                     _mm_mul_pd(
                             _mm_load_pd(&values[i]),
                             _mm_load_pd(&other.values[i])));
        
    }
    
//    for (int i = 0; i < size; i++) {
//        this->values[i] *= other(i);
//    }
}

DenseVector &DenseVector::hadamardNew(DenseVector &other) {
    DenseVector *vec = new DenseVector(*this);
    vec->hadamardSelf(other);
    return *vec;
}

void DenseVector::scaleSelf(double scalar) {
    
//    __m128d sc = _mm_load1_pd(&scalar);
//
//    for(int i = 0; i < size; i+=2){
//
//        _mm_store_pd(&values[i],
//                     _mm_mul_pd(
//                             _mm_load_pd(&values[i]),
//                             sc));
//
//    }
    
    for (int i = 0; i < size; i++) {
        this->values[i] *= scalar;
    }
}

DenseVector &DenseVector::scaleNew(double scalar) {
    DenseVector *vec = new DenseVector(*this);
    vec->scaleSelf(scalar);
    return *vec;
}

double DenseVector::dot(DenseVector &other) {
//    double k = 0;
    
    __m128d sums = _mm_setzero_pd();
    
    for(int i = 0; i < size; i+=2){
    
        sums = _mm_add_pd(
                sums,
                _mm_mul_pd(_mm_load_pd(&values[i]), _mm_load_pd(&other.values[i])));
    
    }
    
    return sums[0]+sums[1];
}

double DenseVector::norm(int norm) {
    double k = 0;
    for(int i = 0; i < size; i++){
        k += pow(values[i], norm);
    }
    return pow(k,1.0/norm);
}

DenseVector &DenseVector::operator+(DenseVector &other) {
    return addNew(other);
}

void DenseVector::operator+=(DenseVector &other) {
    addSelf(other);
}

DenseVector &DenseVector::operator-(DenseVector &other) {
    return subNew(other);
}

void DenseVector::operator-=(DenseVector &other) {
    return subSelf(other);
}

DenseVector &DenseVector::operator*(DenseVector &other) {
    return hadamardNew(other);
}

void DenseVector::operator*=(DenseVector &other) {
    return hadamardSelf(other);
}

DenseVector &DenseVector::operator*(double other) {
    return scaleNew(other);
}

void DenseVector::operator*=(double other) {
    return scaleSelf(other);
}

double DenseVector::operator&(DenseVector &other) {
    return dot(other);
}


double &DenseVector::operator()(int index) {
    return at(index);
}

double DenseVector::operator()(int index) const {
    return get(index);
}

double DenseVector::operator~() {
    return norm(2);
}

DenseVector &DenseVector::operator=(const DenseVector &other) {
    if(this->size != other.size){
        delete[] this->values;
        this->values = new double[other.size + other.size % 2];
    }
    this->size = other.size;
    memcpy(values, other.values, size * sizeof(double));
    return *this;
}

DenseVector &DenseVector::operator=(DenseVector &&other) {
    this->values = other.values;
    this->size = other.size;
    other.values = nullptr;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const DenseVector &vector) {
    os << "[";
    for (int i = 0; i < vector.size; i++) {
        os << vector(i);
        if (i != vector.size - 1) os << ", ";
    }
    return os << "]" << std::endl;
}

bool DenseVector::operator==(const DenseVector &rhs) const {
    if(size != rhs.size) return false;
    for(int i = 0; i < size; i++){
        if(get(i) != rhs.get(i)) return false;
    }
    return true;
}

bool DenseVector::operator!=(const DenseVector &rhs) const {
    return !(rhs == *this);
}
