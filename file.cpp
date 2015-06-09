#include <iostream>
#include "file.h"

FileReader::FileReader(const char * name) {
    filename = (char*)name;
    infile.open(filename);
    
    if(!infile.is_open()){
        std::cout<<"lol";
        exit(1);
    }
}
FileReader::FileReader() {
}

FileReader::~FileReader(){
    infile.close();
}

std::vector<std::string> FileReader::getLines(void){
    char string[150];
    std::vector<std::string> lines;
    if (infile.is_open()) {
        while ( infile.getline(string,150) ) {
            lines.push_back(string);
        }
    }
    return lines;
}

std::vector<std::string> &FileReader::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> FileReader::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void FileReader::writeFile(std::vector<std::string> text) {
    outfile.open("/Users/Levan/xcode/localDB/localDB/Report.txt");
    
    for(std::vector<std::string>::iterator it = text.begin(); it != text.end(); ++it) {
        outfile << *it <<std::endl;
    }
    
    outfile.close();
}

