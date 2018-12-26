//
//  key.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "keyDES.hpp"
#include "stdafx.hpp"
#include "cryptlib.hpp"

using namespace std;

keyDES::keyDES(char * k, int length) {
    setKey(k, length);
}

char * keyDES::getKey() {
    return copyKey(fkey, length);
}

void keyDES::setKey(char * k, int length) {
    fkey = copyKey(k, length);
    this->length = length;
}

char * keyDES::copyKey(const char * key, short length) {
    char * finalKey = new char[length];
    memcpy(finalKey, key, length);
    return finalKey;
}
