#ifndef __localDB__clients__
#define __localDB__clients__

#include <string>
#include <vector>
#include "Param.h"
#include "file.h"

const char clients[] = "/Users/Levan/xcode/localDB/localDB/files/clients.txt";

typedef struct Client{
    int id;
    std::string fio;
    long long phone;
    std::string dateStart;
    std::string dateEnd;
    int debt;
    int credit;
    struct Client * prev;
    struct Client * next;
    
} Client;

class ClientList {

public:
    ClientList();
    ~ClientList();
    int addClient(void);
    
    std::vector<long long> getBalancePhones(double balance);
    
private:
    struct Client * head;
    struct Client * tail;
    int client_size;
    int _id;
    FileReader * fr;
};

#endif