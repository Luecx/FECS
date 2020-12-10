//
// Created by Luecx on 28.11.2020.
//

#ifndef FENIX_ELEMENT_T2D2_H
#define FENIX_ELEMENT_T2D2_H

#include "Element.h"

namespace fem{

class Element_T2D2 : public Element{
public:
    Element_T2D2(int id) : Element(2, id) {}

    Element_T2D2(const Element_T2D2 &other) : Element(other) {}

    Element_T2D2(Element_T2D2 &&other) : Element(other) {}


    DenseMatrix *computeLocalStiffness() override {
        return Element::computeLocalStiffness();
    }

    DenseMatrix *updateJacobian() override {
        return Element::updateJacobian();
    }

    double computeJacobianDeterminant() override {
        return Element::computeJacobianDeterminant();
    }
};
}

#endif //FENIX_ELEMENT_T2D2_H
