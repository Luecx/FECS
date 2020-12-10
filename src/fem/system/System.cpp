//
// Created by Luecx on 27.11.2020.
//

#include "System.h"

double&      fem::System::getSystemContentScalarData(SystemContentScalarDataKey key)                   { return systemContentScalarData[key]; }
double       fem::System::getSystemContentScalarData(SystemContentScalarDataKey key) const             { return systemContentScalarData[key]; }
void         fem::System::setSystemContentScalarData(SystemContentScalarDataKey key, double val)       { systemContentScalarData[key] = val; }
DenseVector& fem::System::getSystemContentVectorData(SystemContentVectorDataKey key)                   { return (systemContentVectorData[key]);}
DenseVector  fem::System::getSystemContentVectorData(SystemContentVectorDataKey key) const             { return (systemContentVectorData[key]);}
void         fem::System::setSystemContentVectorData(SystemContentVectorDataKey key, DenseVector& val) { systemContentVectorData[key] = val; }

double&      fem::System::operator[](fem::SystemContentScalarDataKey key)       { return getSystemContentScalarData(key); }
double       fem::System::operator[](fem::SystemContentScalarDataKey key) const { return getSystemContentScalarData(key); }
DenseVector& fem::System::operator[](fem::SystemContentVectorDataKey key)       { return getSystemContentVectorData(key); }
DenseVector  fem::System::operator[](fem::SystemContentVectorDataKey key) const { return getSystemContentVectorData(key); }

void                        fem::System::addNode        (fem::Node    &&node   , const std::string &nset ) {
    int id = node[GLOBAL_NODE_ID];
    if(nodes.size() <=  id){
        nodes.resize(id+1);
    }
    nodes.at(id) = node;
    if(!nset.empty() && nodeSets.contains(nset)){
        nodeSets[nset].emplace_back(&node);
    }
}
void                        fem::System::addElement     (fem::Element &&element, const std::string &elset) {
    int id = element[GLOBAL_ELEMENT_ID];
    if(elements.size() <= id){
        elements.resize(id+1);
    }
    elements.at(id) = element;
    if(!elset.empty() && elementSets.contains(elset)){
        elementSets[elset].emplace_back(&element);
    }
}
bool                        fem::System::hasNodeSet     (const std::string &nset    ) {
    return nodeSets.contains(nset);
}
bool                        fem::System::hasElementSet  (const std::string &elset   ) {
    return elementSets.contains(elset);
}
std::vector<fem::Node *>    fem::System::getNodeSet     (const std::string &nset    ) {
    if(!hasNodeSet(nset))
        return std::vector<Node*>{};
    return nodeSets[nset];
}
std::vector<fem::Element *> fem::System::getElementSet  (const std::string &elset   ) {
    if(!hasElementSet(elset))
        return std::vector<Element*>{};
    return elementSets[elset];
}


