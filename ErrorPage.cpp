//
// Created by cheng on 2019/4/29.
//

#include "ErrorPage.h"
#include "util.h"
#include <sstream>

using namespace std;

string ErrorPage::get(int reply) {
    switch (reply) {
        case 400:
            return getError400();
        case 404:
            return getError404();
        case 500:
            return getError500();
        case 501:
            return getError501();
    }
    return generate(reply);
}


string ErrorPage::getError400() {
    stringstream ss;

    ss << "<html>" << CRLF;
    ss << "<head><title>Error 400 BAD REQUEST</title></head>" << CRLF;
    ss << "<body><h1>Error 400 BAD REQUEST</h1>" << CRLF;
    ss << "<h3>You sent a bad request.</h3>" << CRLF;
    ss << "</body><html>" << CRLF;

    return ss.str();
}

string ErrorPage::getError404() {
    stringstream ss;

    ss << "<html>" << CRLF;
    ss << "<head><title>Error 404 NOT FOUND</title></head>" << CRLF;
    ss << "<body><h1>Error 404 NOT FOUND</h1>" << CRLF;
    ss << "<h3>The requested page does not exist.</h3>" << CRLF;
    ss << "</body><html>" << CRLF;

    return ss.str();
}

string ErrorPage::getError500() {
    stringstream ss;

    ss << "<html>" << CRLF;
    ss << "<head><title>Error 500 INTERNAL SERVER ERROR</title></head>" << CRLF;
    ss << "<body><h1>Error 500 INTERNAL SERVER ERROR</h1>" << CRLF;
    ss << "</body><html>" << CRLF;

    return ss.str();
}

string ErrorPage::getError501() {
    stringstream ss;

    ss << "<html>" << CRLF;
    ss << "<head><title>Error 501 NOT IMPLEMENTED</title></head>" << CRLF;
    ss << "<body><h1>Error 501 NOT IMPLEMENTED</h1>" << CRLF;
    ss << "</body><html>" << CRLF;

    return ss.str();
}

string ErrorPage::generate(int reply) {
    stringstream ss;

    ss << "<html>" << CRLF;
    ss << "<head><title>Error " << reply << "</title></head>" << CRLF;
    ss << "<body><h1>Error " << reply << "NOT FOUND</h1>" << CRLF;
    ss << "</body><html>" << CRLF;

    return ss.str();
}
