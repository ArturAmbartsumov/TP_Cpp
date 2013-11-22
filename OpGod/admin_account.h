#ifndef ADMIN_ACCOUNT_H
#define ADMIN_ACCOUNT_H

#include <string>
#include <vector>
#include "purse_info.h"
#include "user_info.h"
#include "client.h"

class Admin_Account
{
public:
    Admin_Account(Client&);
    ~Admin_Account();

    //Функция запуска
    void run();

private:
    //Атрибуты
    Client& clnt;
    std::vector<User_Info> user_list; //список юзеров
    User_Info current_user; //текущий юзер
    std::vector<Purse_Info> purse_list; //список кошельков юзера
    std::vector<std::string> server_log; //логи сервера

    //Гет функции
    int get_current_user_info(std::string); //найти юзера по имени и установить его текущим
    int get_current_user_info(int); //найти юзера по Id и установить его текущим
    int get_purse_list(int); //получить список кошельков юзера
    int get_all_user_list(); //получить список всех юзеров
    int get_banned_user_list(); //получить список всех забаненых юзеров
    int get_server_log(); //получить логи сервера

    //Принт функции
    int print_current_user_info(); //печатать инфо ТЕКУЩЕГО юзера
    int print_purse_list(); //печатать список кошельков ТЕКУЩЕГО юзера
    int print_all_user_list(); //печатать список всех юзеров
    int print_banned_user_list(); //печатать список всех забаненных юзеров
    int print_server_log(); //печатать лог сервера

    //Возможности админа
    int logout(); //вернуться в первоначальное меню
    int set_user_ban(bool); //устаносить бан на текущего юзера
    int set_purse_ban(int, bool); //устаносить бан на кощелёк текущего юзера по ID кошелька
    int set_user_ban(int, bool); //устаносить бан на юзера по ID
    int set_purse_ban(int, int, bool); //установить бан на кошелёк по ID юзера и ID кошелька
    int delete_user(); //удалить текущего юзера
    int delete_user(int); //удалить юзера по ID

    //Служебные фукции
    int parse_command(std::string); //парсит входные команды юзера
    //................
};

#endif // ADMIN_ACCOUNT_H
