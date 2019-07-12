//
// Created by cheng on 2019/4/28.
//

#ifndef WEBMIN_UTIL_H
#define WEBMIN_UTIL_H

#include <mutex>
#include <termios.h>

using namespace std;

#define PRINTFLN(fmt...) fprintflnTime(stdout, fmt)
#define PRINTFLN_ERROR(fmt...) fprintflnTime(stderr, fmt)
#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if (p) { delete[] p; p = nullptr; }

#define CRLF "\r\n"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

extern mutex mtx;

void fprintflnTime(FILE *stream, const char *fmt, ...);

#endif //WEBMIN_UTIL_H
