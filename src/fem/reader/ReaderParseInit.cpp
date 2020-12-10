//
// Created by Luecx on 28.11.2020.
//
#include "Reader.h"

void fem::Reader::parse_init() {
    // read the very first line of the file
    currentLine = this->nextLine();
    // read lines until the end of the file is reached
    while(!currentLine.is_end_of_file){

        // raise a warning if the current line is not a key as only keys are parsed below
        if(!currentLine.is_argument){
            this->raiseWarning(1);
        }

        if(currentLine.values[0] == "*NODE"){
            this->parse_nodes();
        }else if(currentLine.values[0] == "*ELEMENT"){
            this->parse_elements();
        }

    }
}
