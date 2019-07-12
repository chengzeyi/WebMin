//
// Created by cheng on 2019/4/28.
//

#include <string>
#include <algorithm>
#include "Mime.h"

using namespace std;

Mime::Mime() = default;

Mime::~Mime() = default;

void Mime::insert(const string &ext, const string &type) {
    mimeMap.emplace(ext, type);
}

const string &Mime::getType(const string &filename) const {
    size_t pos = filename.find_last_of('.');
    if (pos == string::npos) {
        return defaultType;
    }

    pos++;
    string ext = filename.substr(pos);
    for_each(ext.begin(), ext.end(), ::tolower);
    auto &&it = mimeMap.find(ext);
    if (it != mimeMap.end()) {
        return it->second;
    }
    return defaultType;
}

void Mime::setDefaultType(const string &type) {
    defaultType = type;
}
