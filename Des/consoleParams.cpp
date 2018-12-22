//
//  consoleParams.cpp
//  Des
//
//  Created by Виталий on 22.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "consoleParams.hpp"
#include "stdafx.hpp"

using namespace std;

const char oneCode = 49;

const char zeroCode = 48;

bool params::isParamsCorrect() {
    if (count != 3) { //На mac os первый аргумент путь к программе
        cout << "Incorrect number of arguments" << endl;
        return false;
    } else if (!isRightNumber(1, zeroCode, oneCode)) {
        cout << "Incorrect mode. Use only 0 to decrypt and 1 to encrypt" << endl;
        return false;
    } else if (!isFileExist()) {
        cout << "Incorrect path";
        return false;
    }
    return true;
}

bool params::isRightNumber(int i, char bottom, char high) const {
    return (*args[i] >= bottom && *args[i] <= high);
}

bool params::isFileExist() const {
    ifstream f(args[2]);
    return f.is_open();
}
int params::getNumberParam() {
    { return *args[1] - zeroCode; }
}


