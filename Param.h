#ifndef __localDB__Param__
#define __localDB__Param__

#include "file.h"

const char param[] = "/Users/Levan/xcode/localDB/localDB/parameter/Param.ini";

class Param {
public:
    Param();
    ~Param();
    int getMinCountSms();
    double getMinBalance();
private:
    int minCountSum;
    double minBalance;
    FileReader * file;
};

#endif