//
// Created by Luecx on 28.11.2020.
//

#ifndef FENIX_BOUNDARY_H
#define FENIX_BOUNDARY_H


#include "../../linear_algebra/vector/DenseVector.h"
#include "../elements/Node.h"


namespace fem{

struct Boundary {
    // 1 if the dimension is displaced by the given displacement
    DenseVector restrained;
    // equals the displacement at the given node
    DenseVector displacement;


    Boundary(const DenseVector &restrained, const DenseVector &displacement);

    // updates the displacement information
    void applyToNode();

};


}

#endif //FENIX_BOUNDARY_H
