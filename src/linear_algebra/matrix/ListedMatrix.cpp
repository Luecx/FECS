//
// Created by finne on 7/29/2020.
//

#include <cassert>
#include <algorithm>
#include "ListedMatrix.h"

ListedMatrix::ListedMatrix(int mP, int nP) : Matrix(mP, nP) {
    rows = new std::vector<RowEntry>[mP];
    for(int i = 0; i < mP; i++){
        rows[i] = *(new std::vector<RowEntry>());
    }
}

ListedMatrix::ListedMatrix(ListedMatrix &other) : Matrix(other) {
    rows = new std::vector<RowEntry>[other.getM()];
    for(int i = 0; i < other.getM(); i++){
        rows[i] = other.getRow(i);
    }
}

ListedMatrix::~ListedMatrix() {
    for(int i = 0; i < getM(); i++){
        rows[i].clear();
        rows[i].shrink_to_fit();
    }
    
//    delete rows;
}

std::vector<RowEntry> &ListedMatrix::getRow(int row) {
    return rows[row];
}

int ListedMatrix::mem() {
    
    int t = 0;
    
    for(int i = 0; i < getM(); i++){
        t += sizeof(rows[i]);
        t += sizeof(RowEntry) * rows[i].size();
    }
    
    return t + sizeof(int) * 2;
}

void ListedMatrix::reset() {
    for(int i = 0; i < getM(); i++){
        rows[i].clear();
    }
}

void ListedMatrix::set(int m, int n, double val) {
    
    for(int i = 0; i < rows[m].size(); i++){
        if(rows[m].at(i).column == n) {
            rows[m].at(i).value = val;
        }
    }
   
    rows[m].emplace_back(n, val);
}

double &ListedMatrix::at(int m, int n) {
    static int counter = 0;
    
    for(int i = 0; i < rows[m].size(); i++){
        if(rows[m].at(i).column == n) {
            return rows[m].at(i).value;
        }
    }
    
    counter ++;
    rows[m].emplace_back(std::move(RowEntry(n,0)));
    
    return rows[m].back().value;
}

double ListedMatrix::get(int m, int n) const {

    for(int i = 0; i < rows[m].size(); i++){
        if(rows[m].at(i).column == n) {
            return rows[m].at(i).value;
        }
    }
    return 0;
}

void ListedMatrix::copyDataTo(Matrix &other) {
    
    other.reset();
    for(int i = 0; i < getM(); i++){
//        std::sort(rows[i].begin(), rows[i].end());
    
        for(int i = 0; i < rows->size(); i++){
            other.set(i, rows->at(i).column, rows->at(i).value);
        }
        
    }
    
    
}

void ListedMatrix::selfAdd(Matrix &other) {
    
    assert(false);
}

Matrix &ListedMatrix::newAdd(Matrix &other) {
    assert(false);
//    return <#initializer#>;
    return *this;
}


DenseVector &ListedMatrix::mul(DenseVector &vec) {
    assert(false);
    return vec;
}

void ListedMatrix::selfTranspose() {
    exit(-1);
}

Matrix &ListedMatrix::newTranspose() {
    exit(-1);
    return *this;
}

RowEntry::RowEntry(int column, double value) : column(column), value(value) {}



bool RowEntry::operator<(const RowEntry &rhs) const {
    return column < rhs.column;
}

bool RowEntry::operator>(const RowEntry &rhs) const {
    return rhs < *this;
}

bool RowEntry::operator<=(const RowEntry &rhs) const {
    return !(rhs < *this);
}

bool RowEntry::operator>=(const RowEntry &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const RowEntry &entry) {
    os << "column: " << entry.column << " value: " << entry.value;
    return os;
}
