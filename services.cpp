#include "services.h"

ServiceList::ServiceList() {
    fr = new FileReader(services);
    head = tail = NULL;
    _id = 0;
    client_size = 0;
    
    std::vector<std::string> lines = fr->getLines();
    for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
        std::vector<std::string> line = fr->split(*it, ',');
        
        Service *service = new Service;
        service->name = line[0];
        service->code = atoi(line[1].c_str());
        service->tariff = atof(line[2].c_str());
        service->type = (line[3] == " #") ? SERVICE_SMS : SERVICE_MINUTE;

        if(!head) {
            head = tail = service;
        } else {
            service->prev = tail;
            tail->next = service;
            tail = tail->next;
        }
        
        _id++;
        client_size++;
    }
}
void ServiceList::debug(void) {
    Service * first = head;
    Service * n;
    while(first) {
        std::cout << " Название: " << first->name << ".  Номер услуги: " << first->code << ". Тариф: " << first->tariff << ". Тип услуги: " << ((first->type == SERVICE_MINUTE) ? " Минуты" : " СМС") << std::endl;
        n = first->next;
        first = n;
    }
}

ServiceList::~ServiceList() {
    Service * first = head;
    Service * n;
    while(first) {
        n = first->next;
        delete first;
        first = n;
    }
    head = tail = NULL;
    client_size = 0;
    
    delete fr;
}