#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include "Mime.h"
#include "Server.h"
#include "util.h"

#define PORT 8888
#define SERVER_ROOT "."
#define SERVER_FILES "./server-files"
#define CGI_BIN "./cgi-bin"


int main(int argc, char *argv[]) {
    printf("Welcome to WebMin HTTP Server Application\n"
           "\n"
           "usage:\n"
           "\t[port server-root server-files cgi-bin]\n"
           "\n"
           "default values:\n"
           "\tport: '%d'\n"
           "\tserver-root: '%s'\n"
           "\tserver-files: '%s'\n"
           "\tcgi-bin: '%s'\n"
           "The server will listen to the port after start.\n"
           "Any request that has a URL in its request line with a prefix of '/cgi/'\n"
           "will trigger CGI execution by invoking CGI scripts and programs under cgi-bin.\n"
           "The other requests will be treated as plain file requests,\n"
           "by responding with files under server-files.\n"
           "If you want to exit the program, just kill it.\n",
           PORT, SERVER_ROOT, SERVER_FILES, CGI_BIN);

    if (argc != 1 && argc != 5) {
        fprintf(stderr, "invalid number of argument\n");
        return 1;
    }

    int port = PORT;
    string serverRoot = SERVER_ROOT;
    string serverFiles = SERVER_FILES;
    string cgiBin = CGI_BIN;

    if (argc == 5) {
        port = stoi(argv[1]);
        serverRoot = argv[2];
        serverFiles = argv[3];
        cgiBin = argv[4];
    }

    Mime mime;
    const char *ext2Type[] = {
            "html", "text/html",
            "htm", "text/html",
            "jpeg", "image/jpg",
            "jpg", "image/jpg",
            "css", "text/css",
            "js", "application/javascript",
            "json", "application/json",
            "txt", "text/plain",
            "gif", "image/gif",
            "png", "image/png"
    };

    for (size_t i = 0; i < sizeof(ext2Type) / sizeof(const char *); i += 2) {
        mime.insert(ext2Type[i], ext2Type[i + 1]);
    }

    mime.setDefaultType("application/octet-stream");

    Server server(serverRoot, serverFiles, cgiBin, mime);
    if (!server.init(port)) {
        return 1;
    }

    while (true) {
        server.handleHTTPRequest();
    }
    return 0;
}