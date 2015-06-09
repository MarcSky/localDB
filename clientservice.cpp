#include "clientservice.h"

ClientServiceList::ClientServiceList() {
    fr = new FileReader(events); //обьявляем обьект класса filereader для чтения файла clientservice.txt
    head = tail = NULL;
    _id = 0;
    client_size = 0;
    
    std::vector<std::string> lines = fr->getLines(); // поличаем массив строк с файлика
    for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) { //читаем массив строк по одной штуке
        std::vector<std::string> line = fr->split(*it, ','); // split - функция которая делит строки по разделителям в нашем случае запятая
        
        ClientService *clientService = new ClientService; //для каждой строки файла создаем обьект класса и кладет туда инфу с этой строки
        clientService->phone = atoll(line[0].c_str());
        clientService->id_service = atoi(line[1].c_str());
        clientService->dateStart = line[2];
        clientService->time = (line[3] == " #") ? EVENT_SMS : EVENT_SECONDS;
        if(!head) { // тут код работы с листамим
            head = tail = clientService;
        } else {
            clientService->prev = tail;
            tail->next = clientService;
            tail = tail->next;
        }
        
        _id++; //не использую просто написал типо у каждого листа свой номер как в базе данных
        client_size++; //количество строки в файле
    }
}

ClientServiceList::~ClientServiceList() { //удаляем все фигню после выхода из проги чистим память
    ClientService * first = head;
    ClientService * n;
    while(first) {
        n = first->next;
        delete first;
        first = n;
    }
    head = tail = NULL;
    client_size = 0;
    
    delete fr;
}

void ClientServiceList::debug(void) { //дебаг - функция которая просто выводит инфу из списков
    ClientService * first = head;
    ClientService * n;
    while(first) {
        std::cout << " Телефон: " << first->phone << ".  Номер сервиса: " << first->id_service << ". Дата начала: " << first->dateStart << ". Время: " << first->time << std::endl;
        n = first->next;
        first = n;
    }
}

std::vector<long long> ClientServiceList::getSmsPhones(int minSms){ //получаем массив телефон у которых кол-во смс > minSms
//    std::cout << getUnixtime(head->dateStart) << "!";
    std::vector<long long> phones; //создаю массив данных для телефонов
    long long * phone = new long long[10]; // временный массив телефонов
    int * counter = new int[10]; //временный счетчик смсок с номера
    int count = 0;
    struct ClientService * first = head;
    struct ClientService * n;
    while(first) {
        if((getCurrentUnixtime() - getUnixtime(first->dateStart)) < 604800) { //7 недель
            std::cout << "tut" << std::endl;
            bool flag = false;
            for(int i = 0 ; i < count; i++) {
                if(first->phone == phone[i]) {
                    counter[i]++;
                    flag = true;
                    break;
                }
            }
            if(!flag) {
                phone[count] = first->phone;
                counter[count] = 1;
                count++;
            }
        }
        n = first->next;
        first = n;
    }
    for(int i = 0 ; i < count; i++) {
        if(counter[i] > minSms) {
            phones.push_back(phone[i]);
        }
    }
    delete phone;
    delete counter;
    return phones;

}

int ClientServiceList::getCurrentUnixtime(void) {
    std::time_t t = std::time(0);
    return (int)t;
}

int ClientServiceList::getUnixtime(std::string date) {
    FileReader f;
    time_t rawtime;
    struct tm * timeinfo;
    std::string tt= trim(date);
    std::vector<std::string> p = f.split(tt, ' ');
    if(p.size() > 1) {
        std::vector<std::string> d = f.split(p[0], '.');
        int year = atoi(d[2].c_str());
        int month = atoi(d[1].c_str());
        int day = atoi(d[0].c_str());
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        
        if(p.size()> 2) {
            std::vector<std::string> t = f.split(p[1], ':');
            timeinfo->tm_hour   =atoi(t[0].c_str());         //hours since midnight - [0,23]
            timeinfo->tm_min    = atoi(t[1].c_str());          //minutes after the hour - [0,59]
            timeinfo->tm_sec    = atoi(t[2].c_str());          //seconds after the minute - [0,59]
        }
        timeinfo->tm_year   = year - 1900;
        timeinfo->tm_mon    = month - 1;    //months since January - [0,11]
        timeinfo->tm_mday   = day;          //day of the month - [1,31]

        int date = (int)mktime(timeinfo);
        return date;
    }
    return -1;
}
