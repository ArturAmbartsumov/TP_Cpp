/*
 * Input_Module.h
 *
 *  Created on: 22 нояб. 2013 г.
 *      Author: arthur
 */

#ifndef INPUT_MODULE_H_
#define INPUT_MODULE_H_

#include <string>

class Input_Module {
public:
    Input_Module();
    ~Input_Module();

    int read_value(int &);
    int read_value(double &);
    int read_value(std::string &);
    int read_value(bool &);
};

#endif /* INPUT_MODULE_H_ */
