#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#include <string>
#include <vector>
#include "purse_info.h"
#include "user_info.h"
#include "client.h"

class User_Account
{
public:
    User_Account(Client&);
    ~User_Account();

    //Функция запуска
    void run();

private:
    //Атрибуты
    Client& clnt;
    User_Info user; //текущий юзер
    std::vector<Purse_Info> purse_list; //список кошельков юзера

    //Гет функции
    int get_user(); //читает из сокета юзер инфо и записывает в атрубут user
    int get_purse_list(); //получить список своих кошельков

    //Принт функции
    int print_user(); //печатает инфу о озере
    int print_purse_list(); //печатает список кошельков
    int print_purse_info(int); //печатает инфу кошелька по ID

    //Возможности юзера
    int create_purse(int); //создаёт кошелёк указанного типа, обновляет информацию о кошельках
    int delete_purse(int); //удаляет кошелёк по указанному id
    int withdraw_maney(int); //снять деньги с кошелька, указанного по ID
    int withdraw_all(); //снять все деньги со всех кошельков
    int send_maney(int); //сделать перевод на указанный кошелёк

    //Сервисные функции
    int parse(std::string); //парсит входящую строку
    //...................
};

#endif // USER_ACCOUNT_H
