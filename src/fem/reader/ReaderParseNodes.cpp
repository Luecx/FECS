//
// Created by Luecx on 28.11.2020.
//
#include "Reader.h"

void fem::Reader::parse_nodes() {


    std::string setName = this->currentLine.extractValue("NSET");

    this->nextLine();

    while(!currentLine.is_argument){
        // extract x, y and z as well as the id
        int   id = stof(currentLine.values[0]);
        float x  = stof(currentLine.values[1]);
        float y  = stof(currentLine.values[2]);
        float z  = stof(currentLine.values[3]);

        // add it to the system
        system->addNode({{x,y,z},id}, setName);
        system->nodes.push_back({{x,y,z},id});
        nextLine();
    }
}

