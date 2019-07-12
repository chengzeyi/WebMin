//
// Created by cheng on 2019/5/25.
//

#include <cstdio>
#include <ctime>
#include <mutex>
#include <cstdarg>
#include <unistd.h>
#include <termios.h>
#include <termio.h>
#include <fcntl.h>
#include "util.h"

struct termios stdinOrig;

mutex mtx;

void fprintflnTime(FILE *stream, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    time_t rawTime;
    tm *timeInfo;

    char dateTime[32];
    time(&rawTime);
    timeInfo = localtime(&rawTime);

    strftime(dateTime, sizeof(dateTime), "[%x - %X]", timeInfo);

    mtx.lock();
    fprintf(stream, "%s ", dateTime);
    vfprintf(stream, fmt, ap);
    fprintf(stream, "\n");
    fflush(stream);
    mtx.unlock();
}
