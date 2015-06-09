#ifndef __localDB__file__
#define __localDB__file__
#include <fstream>
#include <vector>
#include <sstream>

class FileReader {
public:
    FileReader(const char * name);
    FileReader();
    ~FileReader();
    std::vector<std::string>  getLines(void);
    void writeFile(std::vector<std::string> text);
    std::vector<std::string> split(const std::string &s, char delim);

private:
    char * filename;
    std::ifstream infile;
    std::ofstream outfile;
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
};


#endif