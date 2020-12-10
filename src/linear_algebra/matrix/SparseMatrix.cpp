//
// Created by finne on 7/28/2020.
//

#include <cassert>
#include <algorithm>
#include <emmintrin.h>
#include "SparseMatrix.h"


SparseMatrix::SparseMatrix(int mP, int nP) : Matrix(mP, nP) {
    this->values = *(new std::vector<double>());
    this->row_ptr = *(new std::vector<int>());
    this->col_index = *(new std::vector<int>());
    for (int i = 0; i < this->getM() + 1; i++) {
        row_ptr.push_back(0);
    }
}

SparseMatrix::SparseMatrix(SparseMatrix &other) : Matrix(other) {
    this->values = other.values;
    this->row_ptr = other.row_ptr;
    this->col_index = other.col_index;
}

SparseMatrix::SparseMatrix(ListedMatrix hashMatrix) : Matrix(hashMatrix){
    this->values = *(new std::vector<double>());
    this->row_ptr = *(new std::vector<int>());
    this->col_index = *(new std::vector<int>());
    
    row_ptr.push_back(0);
    int total = 0;
    for (int i = 0; i < hashMatrix.getM(); i++) {
        std::vector<RowEntry> map = hashMatrix.getRow(i);
        total += map.size();
        row_ptr.emplace_back(total);
        
        std::sort(map.begin(), map.end());
        
        
        
        for (int n = 0; n < map.size(); n++) {
            col_index.emplace_back(map.at(n).column);
            values.emplace_back(map.at(n).value);
        }
    }
}



void SparseMatrix::reset() {
    this->values.clear();
    this->row_ptr.clear();
    this->col_index.clear();
    for (int i = 0; i < this->getM() + 1; i++) {
        row_ptr.push_back(0);
    }
}

void SparseMatrix::set(int m, int n, double val) {
    int insertIndex = row_ptr.at(m + 1);
    for (int i = row_ptr.at(m); i < row_ptr.at(m + 1); i++) {
        if (col_index.at(i) < n) {
            continue;
        } else if (col_index.at(i) == n) {
            values.at(i) = val;
            return;
        } else if (col_index.at(i) > n) {
            insertIndex = i;
            break;
        }
    }
    col_index.insert(col_index.begin() + insertIndex, n);
    values.insert(values.begin() + insertIndex, val);
    for (int i = m + 1; i < getM() + 1; i++) {
        row_ptr.at(i) = row_ptr.at(i) + 1;
    }
}

double &SparseMatrix::at(int m, int n) {
    for (int i = row_ptr.at(m); i < row_ptr.at(m + 1); i++) {
        if (col_index.at(i) == n) {
            return values.at(i);
        }
    }
    
    set(m,n,0);
    return at(m,n);
}

double SparseMatrix::get(int m, int n) const {
    for (int i = row_ptr.at(m); i < row_ptr.at(m + 1); i++) {
        if (col_index.at(i) == n) {
            return values.at(i);
        }
    }
    return 0;
}

void SparseMatrix::copyDataTo(Matrix &other) {

}

void SparseMatrix::selfAdd(Matrix &other) {

}

Matrix &SparseMatrix::newAdd(Matrix &other) {
    assert(false);
    return other;
    //    return n;
}

DenseVector &SparseMatrix::mul(DenseVector &vec) {
    DenseVector *out = new DenseVector(getM());
    
    
    for(int i = 0; i < getM(); i++){
        
        
        double sum = 0;
        for (int n = row_ptr.at(i); n < row_ptr.at(i + 1); n++) {
            sum += vec.at(col_index.at(n)) * this->values.at(n);
        }
        out->set(i,sum);
    }
    
    
    return *out;
}


void SparseMatrix::printCSRFormat() {
    std::cout << ("values    :");
    for (int i = 0; i < values.size(); i++) {
        std::cout << std::setw(5) << values.at(i);
    }
    std::cout << "\ncol_index :";
    for (int i = 0; i < col_index.size(); i++) {
        std::cout << std::setw(5) << col_index.at(i);
    }
    std::cout << "\nrow_ptr.  :";
    for (int i = 0; i < row_ptr.size(); i++) {
        std::cout << std::setw(5) << row_ptr.at(i);
    }
    std::cout << std::endl;
}

int SparseMatrix::mem() {
    return
     2 * sizeof(int) +
     1 * sizeof(std::vector<double>) + (sizeof(double) * values.size()) +
     1 * sizeof(std::vector<int>) + (sizeof(int) * row_ptr.size()) +
     1 * sizeof(std::vector<int>) + (sizeof(int) * col_index.size());
}

const std::vector<double> &SparseMatrix::getValues() const {
    return values;
}

const std::vector<int> &SparseMatrix::getColIndex() const {
    return col_index;
}

const std::vector<int> &SparseMatrix::getRowPtr() const {
    return row_ptr;
}

void SparseMatrix::selfTranspose() {
    exit(-1);
}

SparseMatrix &SparseMatrix::newTranspose() {
    exit(-1);
    return *this;
}


