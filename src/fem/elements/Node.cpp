//
// Created by finne on 8/29/2020.
//

#include "Node.h"

double&      fem::Node::getNodeContentScalarData(NodeContentScalarDataKey key)                   { return nodeContentScalarData[key]; }
double       fem::Node::getNodeContentScalarData(NodeContentScalarDataKey key) const             { return nodeContentScalarData[key]; }
void         fem::Node::setNodeContentScalarData(NodeContentScalarDataKey key, double val)       { nodeContentScalarData[key] = val; }
DenseVector& fem::Node::getNodeContentVectorData(NodeContentVectorDataKey key)                   { return (nodeContentVectorData[key]);}
DenseVector  fem::Node::getNodeContentVectorData(NodeContentVectorDataKey key) const             { return (nodeContentVectorData[key]);}
void         fem::Node::setNodeContentVectorData(NodeContentVectorDataKey key, DenseVector& val) { nodeContentVectorData[key] = val; }

double&      fem::Node::operator[](fem::NodeContentScalarDataKey key)       { return getNodeContentScalarData(key); }
double       fem::Node::operator[](fem::NodeContentScalarDataKey key) const { return getNodeContentScalarData(key); }
DenseVector& fem::Node::operator[](fem::NodeContentVectorDataKey key)       { return getNodeContentVectorData(key); }
DenseVector  fem::Node::operator[](fem::NodeContentVectorDataKey key) const { return getNodeContentVectorData(key); }

