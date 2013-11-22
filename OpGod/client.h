#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string.h>

using namespace boost::asio;

class Client {
public:
    Client(io_service&, std::string _ip_addr, unsigned short _port);

    void connect_();
    void close_();

    size_t read_(char[], size_t);
    size_t read_line_(char[]);
    size_t read_until_(char*, const char _until);

    void write_(const std::string&);
private:
    size_t read_complete_(char _buf[], const char _until, size_t _bytes);

    ip::tcp::socket socket_;
    std::string ip_addr_;
    unsigned short port_;
    ip::tcp::endpoint endpoint_;
};


#endif /* CLIENT_HPP_ */
