#ifndef USER_INFO_H
#define USER_INFO_H

#include <string>

struct User_Info {
    int id;
    std::string name;
    std::string surname;
    std::string email;
    std::string registration_date;
    bool ban;
    User_Info(): id(0), name("Ivan"),  surname("Ivanov"), email("ivan@ivanov.ru"), registration_date("00/00/00"), ban(1) {}
};

#endif // USER_INFO_H
