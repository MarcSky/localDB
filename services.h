#ifndef __localDB__services__
#define __localDB__services__

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "file.h"

const char services[] = "/Users/Levan/xcode/localDB/localDB/files/services.txt";

enum SERVICE_TYPE{SERVICE_MINUTE=0, SERVICE_SMS};

typedef struct Service{
    int id;
    std::string name;
    int code;
    float tariff;
    int type;
    Service * prev;
    Service * next;
} Service;

class ServiceList {
public:
    ServiceList();
    ~ServiceList();
    
    void debug(void);

private:
    Service * head;
    Service * tail;
    
    FileReader * fr;
    int client_size;
    int _id;
};


#endif /* defined(__localDB__services__) */
