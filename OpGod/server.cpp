#include "server.h"

const char END_LINE = '\n';

Socket::Socket(boost::asio::io_service& _io_service) : socket_ (_io_service) {}

size_t Socket::read_complete_(char _buf[], const char _until, size_t _bytes) {
    bool found = std::find(_buf, _buf + _bytes, _until) < _buf + _bytes;
    return found ? 0 : 1;
}

size_t Socket::read_(char _buf[], size_t _size) {
    return boost::asio::read(socket_, buffer(&_buf[0], _size));
}

size_t Socket::read_until_(char _buf[], const char _until) {
    mutable_buffers_1 buf = buffer(_buf, 1024);
    return boost::asio::read(socket_, buf,
            boost::bind(&Socket::read_complete_, this, _buf, _until, _2));
}

size_t Socket::read_line_(char _buf[]) {
    return read_until_(_buf, END_LINE);
}

void Socket::write_(const std::string& _buf) {
    socket_.write_some(buffer(_buf));
}

void Socket::close_() {
    socket_.close();
}

Acceptor::Acceptor(io_service& _io_service, unsigned short _port) :
        port_ (_port),
        endpoint_(ip::tcp::v4(),_port),
        acceptor_ (_io_service, endpoint_)
{
    /*void*/
}

void Acceptor::accept_(Socket& socket) {
    acceptor_.accept(socket.socket_);
}
