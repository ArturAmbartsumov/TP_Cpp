#include "client.h"

const char END_LINE = '\n';

Client::Client(io_service& _io_service, std::string _ip_addr, unsigned short _port)
    : socket_(_io_service),
      ip_addr_ (_ip_addr),
      port_ (_port),
      endpoint_(ip::address_v4::from_string(ip_addr_), port_)
{
    /*void*/
}

void Client::connect_() {
    socket_.connect(endpoint_);
}

void Client::close_() {
    socket_.close();
}

size_t Client::read_complete_(char _buf[], const char _until, size_t _bytes) {
    bool found = std::find(_buf, _buf + _bytes, _until) < _buf + _bytes;
    return found ? 0 : 1;
}

size_t Client::read_(char _buf[], size_t _size) {
    return boost::asio::read(socket_, buffer(&_buf[0], _size));
}

size_t Client::read_until_(char _buf[], const char _until) {
    mutable_buffers_1 buf = buffer(_buf, 1024);
    return boost::asio::read(socket_, buf,
            boost::bind(&Client::read_complete_, this, _buf, _until, _2));
}

size_t Client::read_line_(char _buf[]) {
    return read_until_(_buf, END_LINE);
}

void Client::write_(const std::string& _buf) {
    socket_.write_some(buffer(_buf));
}
