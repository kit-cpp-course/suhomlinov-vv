//
//  main.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "stdafx.hpp"
#include "fileEditor.hpp"
#include "Keys.hpp"
#include "key.hpp"
#include "File.hpp"
#include "fileEditor.hpp"
#include "encryption.hpp"
#include "Contents.hpp"
#include "consoleParams.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    int mode;
    string path;

    params param(argc, argv);

    if (param.isParamsCorrect()) {
        mode = param.getNumberParam();
        path = param.getStringParam();

        key key1;
        Keys & k = key1;
        editor editor1(path, mode);
        encryption enc(k, mode);
        File & file = editor1;
        Contents & content = enc;

        while (file.isEnd()) {
            file.reading(blockLength);
            file.writing(content);
        }

        if (mode) cout << "file was encrypted" << endl;
        else cout << "file was decrypted" << endl;
    }

    return 0;
}
