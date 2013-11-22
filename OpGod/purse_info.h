#ifndef PURSE_INFO_H
#define PURSE_INFO_H

#include <string>

struct Purse_Info {
    int id;
    std::string type;
    double balance;
    std::string creation_date;
    bool ban;
    Purse_Info(): id(0), type("RU"), balance(0), creation_date("00/00/00"), ban(1) {}
};

#endif // PURSE_INFO_H
