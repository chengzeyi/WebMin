//
// Created by cheng on 2019/4/29.
//

#ifndef WEBMIN_ERRORPAGE_H
#define WEBMIN_ERRORPAGE_H

#include <string>

using namespace std;

class ErrorPage {
public:
    static string get(int reply);

private:
    static string getError400();

    static string getError404();

    static string getError500();

    static string getError501();

    static string generate(int reply);
};


#endif //WEBMIN_ERRORPAGE_H
