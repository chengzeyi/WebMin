//
// Created by cheng on 2019/4/28.
//

#ifndef WEBMIN_SOCKETFD_H
#define WEBMIN_SOCKETFD_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "Data.h"

using namespace std;

class SocketFD {
public:
    explicit SocketFD();
    ~SocketFD();
    bool init(int port);
    SocketFD *accept() const;
    bool send(const Data &response) const;
    bool send(const string &response) const;
    Data getLine() const;
    Data receive(size_t n) const;
    string getIpString() const;

private:
    int socketfd;
    explicit SocketFD(int socketfd);
    const static in_addr &getInAddr(const sockaddr &sa)
    {
        return (*reinterpret_cast<const sockaddr_in *>(&sa)).sin_addr;
    }

    static int getListenerSocket(int port);
};


#endif //WEBMIN_SOCKETFD_H
