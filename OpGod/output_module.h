#ifndef OUTPUT_MODULE_H
#define OUTPUT_MODULE_H

#include <string>
#include <vector>
#include "user_info.h"
#include "purse_info.h"

class Output_Module
{
public:
    Output_Module();
    ~Output_Module();

    //Поля вывода информации
    void print_menu(std::string); //через него выводить всю информацию по навигации
    void print_central(std::string); //центральное поле - сюда выводить все запросы к пользователю(например: введите логин или ваш баланс столько-то)
    void print_errorfield(std::string); //сюда все ошибки

    //Шаблоны вывода
    void print_admin_menu_tmp(); //шаблон для вывода главного меню админа
    void print_user_menu_tmp(); //шаблон для вывода главного меню юзера
    void print_info_tmp(User_Info); //шаблон для вывода подробной информации о пользователе
    void print_userlist_tmp(std::vector<User_Info>); //шаблон для вывода списка юзеров для админа
    void print_purse_info_tmp(Purse_Info); //шаблон для вывода подробной информации о кошельке
    void print_purselist_tmp(std::vector<Purse_Info>); //шаблон для вывода списка кошельков
    //..............
    //..............

    //нужно только для консоли
    void clear_screen();
};

#endif // OUTPUT_MODULE_H
