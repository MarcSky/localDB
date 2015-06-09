#ifndef __localDB__clientservice__
#define __localDB__clientservice__

#include <stdio.h>
#include <string>
#include <vector>
#include "file.h"
#include <iostream>
#include <ctime>
const char events[] = "/Users/Levan/xcode/localDB/localDB/files/events.txt";

enum EVENTS_TYPE{EVENT_SECONDS=0, EVENT_SMS};

typedef struct ClientService{ //список услуг для клиента
    long long phone;
    int id_service;
    std::string dateStart;
    int time;
    ClientService * next;
    ClientService * prev;

} ClientService;

struct ClientServiceList {
public:
    ClientServiceList();
    ~ClientServiceList();
    std::vector<long long> getSmsPhones(int minSms);
    int getCurrentUnixtime(void);
    int getUnixtime(std::string date);
    void debug(void);
    private:
    ClientService * head;
    ClientService * tail;
    
    FileReader * fr;
    int client_size;
    int _id;
};


#endif /* defined(__localDB__clientservice__) */
