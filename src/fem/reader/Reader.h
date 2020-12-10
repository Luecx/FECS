//
// Created by Luecx on 28.11.2020.
//

#ifndef FENIX_READER_H
#define FENIX_READER_H


#include <string>
#include <fstream>
#include <ostream>
#include "../system/System.h"

namespace fem{

struct ReaderLine{

    // parses the next line and checks the type of line (comment, argument etc)
    void readLine(std::string& line){
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        std::stringstream  ss(line);
        std::string str;
        valueCount = 0;
        while (getline(ss, str, ',')) {
            values[valueCount] = str;
            valueCount++;

        }

        is_empty    = valueCount == 0;
        is_comment  = this->values[0].length() >= 2 && this->values[0][0] == '*' && this->values[0][1] == '*';
        is_argument = this->values[0].length() >= 1 && this->values[0][0] == '*';
    }

    // used if the line contains a key similar to: ,KEY=value,...
    // it will return the value
    std::string extractValue(const std::string& key){
        for(int i = 0; i < valueCount; i++){
            if(values[i].rfind(key, 0) == 0){
                return values[i].substr(key.length() + 1, values[i].length() - key.length() - 1);
            }
        }
        return "";
    }

    // the amount of entries in this line are stored below together with the entries itself
    int         valueCount;
    std::string values[32];
    bool        is_empty       = false;
    bool        is_comment     = false;
    bool        is_argument    = false;
    bool        is_end_of_file = false;

    // tools to display a line and its information
    friend std::ostream &operator<<(std::ostream &os, const ReaderLine &line) {
        for(int i = 0; i < line.valueCount; i++){
            os << std::left << std::setw(20) << line.values[i];
        }
        os      << "\n";
        os      << std::setw(20) << std::left << "valueCount: "       << std::setw(10)    << line.valueCount      << "\n"
                << std::setw(20) << std::left << "is_empty: "         << std::setw(10)    << line.is_empty        << "\n"
                << std::setw(20) << std::left << "is_comment: "       << std::setw(10)    << line.is_comment      << "\n"
                << std::setw(20) << std::left << "is_argument: "      << std::setw(10)    << line.is_argument     << "\n"
                << std::setw(20) << std::left << "is_end_of_file: "   << std::setw(10)    << line.is_end_of_file  << std::endl;
        return os;
    }
};


class Reader {

protected:
    System*         system;
    ReaderLine      currentLine;
    std::fstream    fileStream;

    void parse_init();
    void parse_nodes();
    void parse_elements();

public:

    void readInputDeck(const std::string& inputDeck, System* system){
        fileStream.open(inputDeck, std::ios::in);
        this->system = system;
        if(!fileStream.is_open()){
            raiseError(1);
        }
        parse_init();
    }

    ReaderLine& nextLine(){
        do{
            std::string l;
            if(getline(fileStream, l)){
                currentLine.readLine(l);
            }else{
                currentLine.is_end_of_file = true;
                fileStream.close();
                return currentLine;
            }
        }while (currentLine.is_empty || currentLine.is_comment);
        return currentLine;
    }

    void raiseError(int errorID){
        std::cout << "[ERROR] "<< errorID << std::endl;
        exit(-1);
    }

    void raiseWarning(int errorID){
        std::cout << "[WARNING] "<< errorID << std::endl;
    }
};
}


#endif //FENIX_READER_H
