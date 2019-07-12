//
// Created by cheng on 2019/4/28.
//

#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <unistd.h>
#include "util.h"
#include "SocketFD.h"
#include "Data.h"

#define BACKLOG 10
#define GET_LINE_BUFFER_SIZE 0x10000

using namespace std;

SocketFD::SocketFD() : socketfd(-1) {

}

SocketFD::~SocketFD() {
    if (socketfd >= 0) {
        close(socketfd);
    }
}

bool SocketFD::init(int port) {

    socketfd = getListenerSocket(port);
    return socketfd >= 0;
}

int SocketFD::getListenerSocket(int port) {
    int socketfd;
    addrinfo hints, *servinfo, *p;

    PRINTFLN("started to get listener socket, port: '%d'", port);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int yes = 1;
    int rv;

    if ((rv = getaddrinfo(nullptr, to_string(port).c_str(), &hints, &servinfo)) != 0) {
        PRINTFLN_ERROR("getaddrinfo: '%s'", gai_strerror(rv));
        return -1;
    }

    for (p = servinfo; p != nullptr; p = p->ai_next) {
        if ((socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }

        if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            close(socketfd);
            freeaddrinfo(servinfo);
            return -1;
        }

        if (bind(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(socketfd);
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);

    if (p == nullptr) {
        PRINTFLN_ERROR("failed to find local address");
        return -1;
    }

    if (::listen(socketfd, BACKLOG) == -1) {
        close(socketfd);
        return -1;
    }

    PRINTFLN("finished getting listener socket, port: '%d'", port);

    return socketfd;
}

bool SocketFD::send(const Data &response) const {
    size_t length = response.getLength();
    const char *buffer = response.getBuffer();

//    PRINTFLN("started to send data, data length: '%zu'", length);

    ssize_t bytesSent= ::send(socketfd, buffer, length, 0);
    if (bytesSent < 0) {
        perror("send");
        return false;
    }

//    PRINTFLN("finished sending data, data length: '%zd'", bytesSent);

    return true;
}

SocketFD *SocketFD::accept() const {
    PRINTFLN("accept started");

    sockaddr_storage theirAddr;
    socklen_t sin_size = sizeof(theirAddr);
    int newFD = ::accept(socketfd, (sockaddr *) &theirAddr, &sin_size);
    if (newFD < 0) {
        perror("accept");
        return nullptr;
    }

    PRINTFLN("accept finished");

    return new SocketFD(newFD);
}

SocketFD::SocketFD(int socketfd) : socketfd(socketfd) {

}

Data SocketFD::receive(size_t n) const {
    char *buffer = new char[n];
    Data data;

//    PRINTFLN("started to receive data, buffer size: '%zu'", n);
    ssize_t bytesRecvd = recv(socketfd, buffer, n, 0);
    if (bytesRecvd < 0) {
        perror("recv");
        delete[] buffer;
        return data;
    }
//    PRINTFLN("finished receiving data, data length: '%zd'", bytesRecvd);

    data.moveFromBuffer(buffer, bytesRecvd);

    return data;
}

bool SocketFD::send(const string &response) const {
    Data data;
    data.initFromString(response);
    return send(data);
}

Data SocketFD::getLine() const {
    char *buffer = new char[GET_LINE_BUFFER_SIZE];

    ssize_t numRead;
    size_t toRead = 0;
    char ch, *ptr = buffer;
    Data data;

//    PRINTFLN("started to get one line by reading, buffer size: '%d'", GET_LINE_BUFFER_SIZE);
    while (true) {
        numRead = read(socketfd, &ch, 1);

        if (numRead == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                delete[] buffer;
                return data;
            }
        } else if (numRead == 0) {
            return data;
        } else {
            if (toRead < GET_LINE_BUFFER_SIZE) {
                toRead++;
                *ptr++ = ch;
            }
            if (ch == '\n') {
                break;
            }
        }
    }

//    PRINTFLN("finished getting one line by reading, line length: '%zu'", toRead);
    data.moveFromBuffer(buffer, toRead);
    return data;
}

string SocketFD::getIpString() const {
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(addr);
    if (getpeername(socketfd, (struct sockaddr *)&addr, &addr_size) != 0) {
        return "unknown";
    }
    return string(inet_ntoa(addr.sin_addr));
}
