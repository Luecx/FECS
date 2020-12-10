#include <iostream>
#include <vector>

#include "src/linear_algebra/vector/DenseVector.h"
#include "src/fem/elements/Node.h"
#include "src/fem/reader/Reader.h"
#include "src/fem/elements/Element_T2D2.h"

int main() {
    fem::Reader reader{};
    fem::System system{};

    reader.readInputDeck("../res/test.inp", &system);
//
//
//    std::cout << system.elements.size() << std::endl;

//    using namespace fem;
//    std::vector<Node> vector;
//    vector.resize(1);
//    std::cout << vector[0][POSITION].getSize() << std::endl;


//    DenseVector vectors[10]{};
//    std::cout << vectors[3].getSize()<< std::endl;

}
