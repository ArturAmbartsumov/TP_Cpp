#include <stdio.h>

#include "server.h"

int main() {
    io_service io_service;

    Acceptor acceptor(io_service, 4321);
    char buf[1024];

    while(true) {
        printf("Initialization is completed\n");
        Socket socket(io_service);

        printf("Waiting for client\n");
        acceptor.accept_(socket);
        printf("A client has accepted\n");
        int bytes = socket.read_line_(buf);

        if (bytes != 0)
            std::cout << buf << std::endl;
        else
            std::cout << "Read error" << std::endl;

        printf("read %d bytes\n", bytes);
        std::string msg("Hello, Client!\n");
        socket.write_(msg);
        socket.close_();
    }

    return 0;
}
