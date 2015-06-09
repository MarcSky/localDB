#include "clients.h"
#include <iostream>

ClientList::ClientList(){
    head = tail = NULL;
    _id = 0;
    client_size = 0;
    fr = new FileReader(clients);
    
    std::vector<std::string> lines = fr->getLines();
    for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
//        std::cout << *it << std::endl;
        std::vector<std::string> line = fr->split(*it, ',');
        
        Client *client = new Client;
        client->fio = line[0]; // фамилия имя отчество
        client->phone = atoll(line[1].c_str()); //номер телефона
        client->dateStart = line[2]; //Дата начала
        client->dateEnd = line[3]; //Дата конца
        client->debt = atoi(line[4].c_str()); //размер долга
        client->credit = atoi(line[5].c_str()); //размер кредита
        client->prev = client->next = NULL;
        if(!head) {
            head = tail = client;
        } else {
            client->prev = tail;
            tail->next = client;
            tail = tail->next;
        }
        _id = 0;
        client_size++;
    }
}

ClientList::~ClientList(){
    struct Client * first = head;
    struct Client * n;
    while(first) {
        n = first->next;
        delete first;
        first = n;
    }
    head = tail = NULL;
    client_size = 0;
    delete fr;
    
}

std::vector<long long> ClientList::getBalancePhones(double balance) {
    std::vector<long long> phones;

    struct Client * first = head;
    struct Client * n;
    while(first) {
        double b = first->credit - first->debt;
        if(b > balance) {
            phones.push_back(first->phone);
        }
        n = first->next;
        first = n;
    }
    return phones;
}


