//
// Created by finne on 7/29/2020.
//

#ifndef MATLIB_LISTEDMATRIX_H
#define MATLIB_LISTEDMATRIX_H


#include <vector>
#include <ostream>
#include "Matrix.h"

struct RowEntry {
    int    column = 0;
    double value  = 0;
    
    bool operator<(const RowEntry &rhs) const;
    
    bool operator>(const RowEntry &rhs) const;
    
    bool operator<=(const RowEntry &rhs) const;
    
    bool operator>=(const RowEntry &rhs) const;
    
    RowEntry(int column, double value);
    
    RowEntry() {}
    
    
    RowEntry(const RowEntry &rowEntry) {
        this->column = rowEntry.column;
        this->value  = rowEntry.value;
    }
    
    
    RowEntry(const RowEntry &&rowEntry) {
        this->column = rowEntry.column;
        this->value  = rowEntry.value;
    }
    
    RowEntry &operator=(const RowEntry &rhs) {
        this->value  = rhs.value;
        this->column = rhs.column;
        return *this;
    }
    
    RowEntry &operator=(RowEntry &&rhs) noexcept // move assignment
    {
        this->value  = rhs.value;
        this->column = rhs.column;
        return *this;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const RowEntry &entry);
};

class ListedMatrix : public Matrix {
        std::vector<RowEntry> *rows;
    public:
        ListedMatrix(int mP, int nP);
        
        ListedMatrix(ListedMatrix &other);
        
        ListedMatrix() = delete;
        
        virtual ~ListedMatrix();
        
        std::vector<RowEntry> &getRow(int row);
        
        int mem() override;
        
        void reset() override;
        
        void set(int m, int n, double val) override;
        
        double &at(int m, int n) override;
        
        double get(int m, int n) const override;
        
        void copyDataTo(Matrix &other) override;
        
        void selfAdd(Matrix &other) override;
        
        Matrix &newAdd(Matrix &other) override;
        
        DenseVector &mul(DenseVector &vec) override;
        
        void selfTranspose() override;
        
        Matrix &newTranspose() override;
    
};


#endif //MATLIB_LISTEDMATRIX_H
