#include "client.h"
#include "user_info.h"
#include "output_module.h"
#include "input_module.h"

int main() {

    Output_Module o;
    Input_Module im;
    Purse_Info user;

    bool a;
    im.read_value(a);
    std::cout << a;

//    std::cout << "Hello world\n";
//    boost::asio::io_service io_service;
//    Client clnt(io_service, "127.0.0.1", 4321);
//    clnt.connect_();

//    std::string buf("Hi, Server!\nIt won't be read");
//    clnt.write_(buf);

//    char buf1[1024];
//    int size;

//    if ((size = clnt.read_line_(buf1)) != 0)
//        std::cout << buf1 << std::endl;
//    else
//        std::cout << "Read error" << std::endl;

//    clnt.close_();
    return 0;
}
