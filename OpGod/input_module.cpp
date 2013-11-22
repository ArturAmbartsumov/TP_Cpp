/*
 * Input_Module.cpp
 *
 *  Created on: 22 нояб. 2013 г.
 *      Author: arthur
 */

#include "input_module.h"
#include <iostream>
#include <cstdlib>
using std::cin;
using std::getline;
using std::string;
using std::strtol;
using std::strtod;

Input_Module::Input_Module() {
}

Input_Module::~Input_Module() {
}

int Input_Module::read_value(int &bar) {
    string line;
    getline(cin, line);
    bar = strtol(line.c_str() ,NULL, 10);
    return 1;
}

int Input_Module::read_value(double &bar) {
    string line;
    getline(cin, line);
    bar = strtod(line.c_str(), NULL);
    return 1;
}

int Input_Module::read_value(std::string &bar) {
    getline(cin, bar);
    return 1;
}

int Input_Module::read_value(bool &bar) {
    string line;
    getline(cin, line);
    bar = strtol(line.c_str() ,NULL, 10);
    return 1;
}
