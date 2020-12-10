//
// Created by Luecx on 27.11.2020.
//

#include "Element.h"

double&      fem::Element::getElementContentScalarData(ElementContentScalarDataKey key)                   { return elementContentScalarData[key]; }
double       fem::Element::getElementContentScalarData(ElementContentScalarDataKey key) const             { return elementContentScalarData[key]; }
void         fem::Element::setElementContentScalarData(ElementContentScalarDataKey key, double val)       { elementContentScalarData[key] = val; }
DenseVector& fem::Element::getElementContentVectorData(ElementContentVectorDataKey key)                   { return (elementContentVectorData[key]);}
DenseVector  fem::Element::getElementContentVectorData(ElementContentVectorDataKey key) const             { return (elementContentVectorData[key]);}
void         fem::Element::setElementContentVectorData(ElementContentVectorDataKey key, DenseVector& val) { elementContentVectorData[key] = val; }

double&      fem::Element::operator[](fem::ElementContentScalarDataKey key)       { return getElementContentScalarData(key); }
double       fem::Element::operator[](fem::ElementContentScalarDataKey key) const { return getElementContentScalarData(key); }
DenseVector& fem::Element::operator[](fem::ElementContentVectorDataKey key)       { return getElementContentVectorData(key); }
DenseVector  fem::Element::operator[](fem::ElementContentVectorDataKey key) const { return getElementContentVectorData(key); }


