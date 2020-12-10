//
// Created by Luecx on 28.11.2020.
//
#include "Reader.h"
#include "../elements/Element_T2D2.h"

void fem::Reader::parse_elements() {

    std::string type = this->currentLine.extractValue("TYPE");

    this->nextLine();
    while(!currentLine.is_argument && !currentLine.is_end_of_file){
        if(type == "T2D2"){
            int id  = std::stoi(currentLine.values[0]);
            int id1 = std::stoi(currentLine.values[1]);
            int id2 = std::stoi(currentLine.values[2]);

            Node* n1 = &system->nodes[id1];
            Node* n2 = &system->nodes[id2];

            Element_T2D2 elementT2D2{id};
            elementT2D2.nodes[0] = n1;
            elementT2D2.nodes[1] = n2;

            system->elements.push_back(elementT2D2);
        }else{
            this->raiseError(2);
        }
        this->nextLine();
    }

}

