#include "output_module.h"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;

Output_Module::Output_Module() {
}

Output_Module::~Output_Module() {
}

void Output_Module::print_central(std::string message) {
    cout << message << endl;
}

void Output_Module::print_menu(std::string menu) {
    cout << menu << endl;
}

void Output_Module::print_errorfield(std::string error) {
    cout << error << endl;
}

void Output_Module::print_info_tmp(User_Info user) {

    cout << endl << "User Information:" << endl
         << "|"
         << setw(10) << "ID |"
         << setw(16) << "Name |"
         << setw(20) << "Surname |"
         << setw(20) << "Email |"
         << setw(20) << "Registration Date |"
         << setw(6) << "Ban |"
         << endl;

    for (int i = 0; i < (10+16+20+20+20+5) + 1; ++i)
        cout << "-";
    cout << endl;

    cout << "|"
         << setw(8) << user.id << " |"
         << setw(14) << user.name << " |"
         << setw(18) << user.surname << " |"
         << setw(18) << user.email << " |"
         << setw(18) << user.registration_date << " |"
         << setw(4) << user.ban << " |"
         << endl;
}

void Output_Module::print_userlist_tmp(std::vector<User_Info> users_list) {

    cout << endl << "Users list:" << endl << endl;

    cout << "|"
         << setw(10) << "ID |"
         << setw(20) << "Name |"
         << setw(20) << "Surname |"
         << setw(6) << "Ban |"
         << endl;

    for (int i = 0; i < (10+20+20+6) + 2; ++i)
        cout << "_";
    cout << endl;

    for (size_t i = 0; i < users_list.size(); ++i) {
        cout << "|"
             << setw(8) << users_list[i].id << " |"
             << setw(18) << users_list[i].name << " |"
             << setw(18) << users_list[i].surname << " |"
             << setw(4) << users_list[i].ban << " |"
             << endl;
    }
}

void Output_Module::print_purse_info_tmp(Purse_Info purse) {

    cout << endl << "User Information:" << endl
         << "|"
         << setw(10) << "ID |"
         << setw(10) << "Type |"
         << setw(10) << "Balance |"
         << setw(16) << "Creation Date |"
         << setw(6) << "Ban |"
         << endl;

    for (int i = 0; i < (10+10+10+16+6) + 1; ++i)
        cout << "-";
    cout << endl;

    cout << "|"
         << setw(8) << purse.id << " |"
         << setw(8) << purse.type << " |"
         << setw(8) << purse.balance << " |"
         << setw(14) << purse.creation_date << " |"
         << setw(4) << purse.ban << " |"
         << endl;
}

void Output_Module::print_purselist_tmp(std::vector<Purse_Info> purse_list) {

    cout << endl << "Users list:" << endl << endl;

    cout << "|"
         << setw(10) << "ID |"
         << setw(10) << "Type |"
         << setw(10) << "Balance |"
         << setw(6) << "Ban |"
         << endl;

    for (int i = 0; i < (10+10+10+6) + 2; ++i)
        cout << "_";
    cout << endl;

    for (size_t i = 0; i < purse_list.size(); ++i) {
        cout << "|"
             << setw(8) << purse_list[i].id << " |"
             << setw(8) << purse_list[i].type << " |"
             << setw(8) << purse_list[i].balance << " |"
             << setw(4) << purse_list[i].ban << " |"
             << endl;
    }
}
