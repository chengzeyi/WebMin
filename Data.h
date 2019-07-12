//
// Created by cheng on 2019/4/29.
//

#ifndef WEBMIN_DATA_H
#define WEBMIN_DATA_H

#include <vector>
#include <string>

using namespace std;

class Data {
public:
    Data();
    ~Data();
    Data(Data &&other);
    Data(const Data &other);
    void moveFromBuffer(const char *buffer, size_t length);
    void initFromBuffer(const char *buffer, size_t length);
    void initFromString(const string &str);
    bool initFromFile(const string &filename);
    const char *getBuffer() const;
    size_t getLength() const;
    string toString() const;

protected:
    char *buffer;
    size_t length;
};


#endif //WEBMIN_DATA_H
