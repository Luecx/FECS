//
// Created by Luecx on 27.11.2020.
//

#ifndef FENIX_ELEMENT_H
#define FENIX_ELEMENT_H

#include "../../linear_algebra/matrix/DenseMatrix.h"
#include "../../linear_algebra/vector/DenseVector.h"
#include "Node.h"

namespace fem{


// the element contains informations beside position and displacement
enum ElementContentScalarDataKey {
    // global id for this element
    GLOBAL_ELEMENT_ID,
    ELEMENT_NODE_COUNT,
    ELEMENT_CONTENT_SCALAR_KEYS
};

// vectorised information in this element
enum ElementContentVectorDataKey {
    ELEMENT_CONTENT_VECTOR_KEYS
};

class Element{
private:

    double              elementContentScalarData[ELEMENT_CONTENT_SCALAR_KEYS]{0};
    DenseVector         elementContentVectorData[ELEMENT_CONTENT_VECTOR_KEYS]{ };
    
public:
    Node** nodes        = nullptr;

    Element(){}
    Element(int nodeCount, int id){
        (*this)[ELEMENT_NODE_COUNT] = nodeCount;
        (*this)[GLOBAL_ELEMENT_ID ] = id;
        this->nodes = new Node*[nodeCount];
    }
    virtual ~Element() {
        delete[] this->nodes;
    }
    Element(const Element& other){
        for(int i = 0; i < ELEMENT_CONTENT_SCALAR_KEYS; i++){
            ElementContentScalarDataKey key = static_cast<ElementContentScalarDataKey>(i);
            (*this)[key] = other[key];
        } for(int i = 0; i < ELEMENT_CONTENT_VECTOR_KEYS; i++){
            ElementContentVectorDataKey key = static_cast<ElementContentVectorDataKey>(i);
            (*this)[key] = other[key];
        }
        this->nodes = new Node*[static_cast<int>((*this)[ELEMENT_NODE_COUNT])];
        for(int i = 0; i < (*this)[ELEMENT_NODE_COUNT]; i++){
            this->nodes[i] = other.nodes[i];
        }
    }
    Element(Element&& other){
        for(int i = 0; i < ELEMENT_CONTENT_SCALAR_KEYS; i++){
            ElementContentScalarDataKey key = static_cast<ElementContentScalarDataKey>(i);
            (*this)[key] = other[key];
        } for(int i = 0; i < ELEMENT_CONTENT_VECTOR_KEYS; i++){
            ElementContentVectorDataKey key = static_cast<ElementContentVectorDataKey>(i);
            (*this)[key] = other[key];
        }
        this->nodes = other.nodes;
        other.nodes = nullptr;
    }
    Element& operator=(const Element& other){
        for(int i = 0; i < ELEMENT_CONTENT_SCALAR_KEYS; i++){
            ElementContentScalarDataKey key = static_cast<ElementContentScalarDataKey>(i);
            (*this)[key] = other[key];
        } for(int i = 0; i < ELEMENT_CONTENT_VECTOR_KEYS; i++){
            ElementContentVectorDataKey key = static_cast<ElementContentVectorDataKey>(i);
            (*this)[key] = other[key];
        }
        for(int i = 0; i < (*this)[ELEMENT_NODE_COUNT]; i++){
            this->nodes[i] = other.nodes[i];
        }
        return *this;
    }
    Element& operator=(Element&& other){
        for(int i = 0; i < ELEMENT_CONTENT_SCALAR_KEYS; i++){
            ElementContentScalarDataKey key = static_cast<ElementContentScalarDataKey>(i);
            (*this)[key] = other[key];
        } for(int i = 0; i < ELEMENT_CONTENT_VECTOR_KEYS; i++){
            ElementContentVectorDataKey key = static_cast<ElementContentVectorDataKey>(i);
            (*this)[key] = other[key];
        }
        this->nodes = other.nodes;
        other.nodes = nullptr;
        return *this;
    }

    double&       getElementContentScalarData(ElementContentScalarDataKey key);
    double        getElementContentScalarData(ElementContentScalarDataKey key) const;
    void          setElementContentScalarData(ElementContentScalarDataKey key, double val);
    DenseVector&  getElementContentVectorData(ElementContentVectorDataKey key);
    DenseVector   getElementContentVectorData(ElementContentVectorDataKey key) const;
    void          setElementContentVectorData(ElementContentVectorDataKey key, DenseVector& val);

    double&       operator[] (ElementContentScalarDataKey key);
    double        operator[] (ElementContentScalarDataKey key) const;
    DenseVector&  operator[] (ElementContentVectorDataKey key);
    DenseVector   operator[] (ElementContentVectorDataKey key) const;

    virtual DenseMatrix* computeLocalStiffness(){return nullptr;}
    virtual DenseMatrix* updateJacobian()       {return nullptr;}
    virtual double computeJacobianDeterminant() {return 0;}

};

}
#endif //FENIX_ELEMENT_H
