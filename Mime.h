//
// Created by cheng on 2019/4/28.
//

#ifndef WEBMIN_MIME_H
#define WEBMIN_MIME_H

#include <string>
#include <unordered_map>

using namespace std;

class Mime {
public:
    Mime();
    ~Mime();
    void setDefaultType(const string &type);
    void insert(const string &ext, const string &type);
    const string &getType(const string &filename) const;

private:
    typedef unordered_map<string, string> MimeMap;
    MimeMap mimeMap;
    string defaultType;
};


#endif //WEBMIN_MIME_H
