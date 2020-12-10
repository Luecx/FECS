//
// Created by Luecx on 27.11.2020.
//

#ifndef FENIX_SYSTEM_H
#define FENIX_SYSTEM_H

#include <vector>
#include <map>
#include "../elements/Node.h"
#include "../elements/Element.h"
#include "../../linear_algebra/matrix/DenseMatrix.h"
#include "../../linear_algebra/vector/DenseVector.h"
#include "../boundary/Boundary.h"


namespace fem{

// the system contains scalar information which can be indexed using the variables below
enum SystemContentScalarDataKey {
    SYSTEM_NODE_DOF,
    SYSTEM_NODE_COUNT,
    SYSTEM_ELEMENT_COUNT,
    SYSTEM_CONTENT_SCALAR_KEYS
};

// vectorised information in this system
enum SystemContentVectorDataKey {
    SYSTEM_CONTENT_VECTOR_KEYS
};

class System {
private:

    double              systemContentScalarData[SYSTEM_CONTENT_SCALAR_KEYS]{0};
    DenseVector         systemContentVectorData[SYSTEM_CONTENT_VECTOR_KEYS]{ };

public:

    std::vector<Node>                               nodes       {};
    std::vector<Element>                            elements    {};
    std::map<std::string, std::vector<Node*>>       nodeSets    {};
    std::map<std::string, std::vector<Element*>>    elementSets {};

    std::vector<Boundary>                           forcedDisplacements {};

    void                    addNode         (Node    &&node   , const std::string& nset=""   );
    void                    addElement      (Element &&element, const std::string& elset=""  );
    bool                    hasNodeSet      (const std::string& nset    );
    bool                    hasElementSet   (const std::string& elset   );
    std::vector<Node*>      getNodeSet      (const std::string& nset    );
    std::vector<Element*>   getElementSet   (const std::string& elset   );


    double&       getSystemContentScalarData(SystemContentScalarDataKey key);
    double        getSystemContentScalarData(SystemContentScalarDataKey key) const;
    void          setSystemContentScalarData(SystemContentScalarDataKey key, double val);
    DenseVector&  getSystemContentVectorData(SystemContentVectorDataKey key);
    DenseVector   getSystemContentVectorData(SystemContentVectorDataKey key) const;
    void          setSystemContentVectorData(SystemContentVectorDataKey key, DenseVector& val);

    double&       operator[] (SystemContentScalarDataKey key);
    double        operator[] (SystemContentScalarDataKey key) const;
    DenseVector&  operator[] (SystemContentVectorDataKey key);
    DenseVector   operator[] (SystemContentVectorDataKey key) const;

};

}

#endif //FENIX_SYSTEM_H
