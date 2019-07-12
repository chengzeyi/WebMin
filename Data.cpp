//
// Created by cheng on 2019/4/30.
//
#include <algorithm>
#include <fstream>
#include "Data.h"
#include "util.h"

using namespace std;

Data::Data() : buffer(nullptr), length(0) {

}

Data::~Data() {
    SAFE_DELETE_ARRAY(buffer);
}

const char *Data::getBuffer() const {
    return buffer;
}

void Data::initFromBuffer(const char *buffer, size_t length) {
    this->buffer = new char[length];
    this->length = length;
    copy(buffer, buffer + length, this->buffer);
}

void Data::initFromString(const string &str) {
    length = str.length();
    buffer = new char[length];
    copy(str.cbegin(), str.cend(), buffer);
}

bool Data::initFromFile(const string &filename) {
    vector<char> container;
    filebuf fb;
    if (fb.open(filename, ios::in)) {
        istream is(&fb);
        container.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());
        length = container.size();
        buffer = new char[length];
        copy(container.cbegin(), container.cend(), buffer);
        return true;
    }
    PRINTFLN_ERROR("open file error, filename: '%s'", filename.c_str());
    return false;
}

void Data::moveFromBuffer(const char *buffer, size_t length) {
    this->buffer = const_cast<char *>(buffer);
    this->length = length;
}

Data::Data(Data &&other) {
    length = other.length;
    buffer = other.buffer;
    other.length = 0;
    other.buffer = nullptr;
}

Data::Data(const Data &other) {
    length = other.length;
    buffer = new char[length];
    copy(other.buffer, other.buffer + length, buffer);
}

size_t Data::getLength() const {
    return length;
}

string Data::toString() const {
    return string(buffer , buffer + length);
}
