#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <string.h>
#include <pthread.h>

#include <boost/regex/user.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

struct Acceptor;
struct Socket {
    friend struct Acceptor;

    Socket(io_service&);

    size_t read_(char[], size_t);
    size_t read_line_(char[]);
    size_t read_until_(char[], const char _until);

    void write_(const std::string&);

    void close_();
private:
    size_t read_complete_(char[], const char _until, size_t bytes);
    ip::tcp::socket socket_;
};

struct Acceptor {
    explicit Acceptor(io_service&, unsigned short _port);

    void accept_(Socket& socket);
private:
    unsigned short port_;
    ip::tcp::endpoint endpoint_;
    ip::tcp::acceptor acceptor_;
};



#endif /* SERVER_HPP_ */
