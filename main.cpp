#include <iostream>
#include <string>
#include <vector>

#include "Param.h"
#include "clients.h"
#include "services.h"
#include "clientservice.h"
#include "file.h"

int main(int argc, const char * argv[]) {

    std::cout << "Start Program" << std::endl;
    
    Param p; //создаем обект класса
    ClientList clientList;  //создаем обект класса
    ServiceList serviceList;  //создаем обект класса
    ClientServiceList clientServiceList;  //создаем обект класса

    double balance = p.getMinBalance();
    int minSms = p.getMinCountSms();
    std::vector<long long> t = clientList.getBalancePhones(balance);
    std::cout << "Количество номер с балансом " << t.size() << std::endl;
    std::vector<long long> s = clientServiceList.getSmsPhones(minSms);
    std::cout << "Текущее количество = " << s.size() << " !" << std::endl;
    
    FileReader f;
    std::vector<std::string> text;
    text.push_back(std::string("start programm"));
    text.push_back(std::string("start phones with balanse > zadanogo"));
    if(t.size() > 0) {
        for(int i = 0; i < t.size(); i++) {
            std::string convert = std::to_string(t[i]);
            text.push_back(convert);
        }
    } else {
        text.push_back(std::string("phones with balance not exist!"));
    }
    text.push_back(std::string("end phones with balanse > zadanogo"));
    text.push_back(std::string("start phones with sms > zadanogo"));
    
    if(s.size() > 0) {
        for(int i = 0; i < s.size(); i++) {
            std::string convert = std::to_string(s[i]);
            text.push_back(convert);
        }
    } else {
        text.push_back(std::string("phones with sms not exist!"));
    }
    
    text.push_back(std::string("end phones with sms > zadanogo"));
    text.push_back(std::string("end programm"));
    f.writeFile(text);
    std::cout << "End Program" << std::endl;
    return 0;
}
