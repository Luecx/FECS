//
// Created by finne on 8/29/2020.
//

#ifndef MATLIB_NODE_H
#define MATLIB_NODE_H

#include "../../linear_algebra/matrix/DenseMatrix.h"
#include "../../linear_algebra/vector/DenseVector.h"

namespace fem {

// the node contains informations beside position and displacement
enum NodeContentScalarDataKey {
    // global id for this node
    GLOBAL_NODE_ID,
    // used to get the entry in the global reduced matrix
    REDUCED_SYSTEM_ID,

    NODE_CONTENT_SCALAR_KEYS
    };

// vectorised information in this node
enum NodeContentVectorDataKey {
    // position of the node
    POSITION,
    // displacement of the node which is part of static analysis
    DISPLACEMENT,
    // acceleration which is relevant for non-static analysis
    ACCELERATION,
    // if a boundary condition is applied, the restrained coordinates will not be part of the final equation
    // as nodes can receive a forced displacement, two vectors are needed.
    RESTRAINED_COORDINATES,
    RESTRAINED_DISPLACEMENT,


    NODE_CONTENT_VECTOR_KEYS
};


class Node {

    double              nodeContentScalarData[NODE_CONTENT_SCALAR_KEYS]{0};
    DenseVector         nodeContentVectorData[NODE_CONTENT_VECTOR_KEYS]{ };

    public:

    Node() {}

    Node(const DenseVector& position, int id)  {
        (*this)[GLOBAL_NODE_ID] = id;
        (*this)[POSITION]       = position;
    }

    Node(int id) {
        (*this)[GLOBAL_NODE_ID] = id;
    }

    double&       getNodeContentScalarData(NodeContentScalarDataKey key);
    double        getNodeContentScalarData(NodeContentScalarDataKey key) const;
    void          setNodeContentScalarData(NodeContentScalarDataKey key, double val);
    DenseVector&  getNodeContentVectorData(NodeContentVectorDataKey key);
    DenseVector   getNodeContentVectorData(NodeContentVectorDataKey key) const;
    void          setNodeContentVectorData(NodeContentVectorDataKey key, DenseVector& val);

    double&       operator[] (NodeContentScalarDataKey key);
    double        operator[] (NodeContentScalarDataKey key) const;
    DenseVector&  operator[] (NodeContentVectorDataKey key);
    DenseVector   operator[] (NodeContentVectorDataKey key) const;
};

}    // namespace fem

#endif    // MATLIB_NODE_H
