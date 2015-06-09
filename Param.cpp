#include <iostream>
#include "Param.h"

Param::Param(){
    file = new FileReader(param);
    std::vector<std::string> lines = file->getLines();
    if(lines.size()) {
        std::vector<std::string> t1 = file->split(lines[0], '=');
        minCountSum = atoi(t1[1].c_str());
        std::cout << minCountSum << std::endl;
    
        std::vector<std::string> t2 = file->split(lines[1], '=');
        minBalance = atof(t2[1].c_str());
        std::cout << minBalance << std::endl;
    }else{
        minCountSum = 0;
        minBalance = 0.0;
    }
}

Param::~Param(){
    delete file;
}

int Param::getMinCountSms() {
    return minCountSum;
}

double Param::getMinBalance() {
    return minBalance;
}

