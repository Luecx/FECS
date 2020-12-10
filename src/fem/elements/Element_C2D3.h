//
// Created by Luecx on 28.11.2020.
//

#ifndef FENIX_ELEMENT_C2D3_H
#define FENIX_ELEMENT_C2D3_H

#include "Element.h"

namespace fem{

    class Iso2DTri3 : public Element{

    private:
        DenseMatrix jacobian {2, 2};
        DenseMatrix inverseJacobian {2, 2};
        DenseMatrix stiffness {6, 6};

    public:
        Iso2DTri3();

        Iso2DTri3(Node* n1, Node* n2, Node* n3);

        DenseMatrix* computeLocalStiffness() override;

        DenseMatrix* updateJacobian() override;

        double computeJacobianDeterminant() override;
    };

}
#endif //FENIX_ELEMENT_C2D3_H
