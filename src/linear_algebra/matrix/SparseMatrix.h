//
// Created by finne on 7/28/2020.
//

#ifndef MATLIB_SPARSEMATRIX_H
#define MATLIB_SPARSEMATRIX_H


#include <vector>
#include "Matrix.h"
#include "ListedMatrix.h"

class SparseMatrix : public Matrix{
    
    private:
    
        std::vector<double> values;
        std::vector<int> col_index;
        std::vector<int> row_ptr;
    
    public:
        
        SparseMatrix(int mP, int nP);
        
        SparseMatrix() = delete;
        
        SparseMatrix(SparseMatrix &other);
        
        SparseMatrix(ListedMatrix hashMatrix);
        
        
        void printCSRFormat();
        
        int mem() override;
        
        void reset() override;
        
        void set(int m, int n, double val) override;
        
        double &at(int m, int n)  override;
        
        double get(int m, int n) const override;
        
        void copyDataTo(Matrix &other) override;
        
        void selfAdd(Matrix &other) override;
        
        Matrix &newAdd(Matrix &other) override;
        
        DenseVector &mul(DenseVector &vec) override;
        
        const std::vector<double> &getValues() const;
        
        const std::vector<int> &getColIndex() const;
        
        const std::vector<int> &getRowPtr() const;
        
        void selfTranspose() override;
        
        SparseMatrix &newTranspose() override;
    
        
        
};


#endif //MATLIB_SPARSEMATRIX_H
