//
//  main.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "stdafx.hpp"
#include "fileEditor.hpp"
#include "keyDES.hpp"
#include "File.hpp"
#include "fileEditor.hpp"
#include "encryptionDES.hpp"
#include "Contents.hpp"
#include "consoleParams.hpp"
#include "KeysGenerator.hpp"
#include "keyFactory.hpp"
#include "Encryption.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    int mode;
    string path;
    
    params param(argc, argv);
    
    try {
         if (param.isParamsCorrect()) {
        
            mode = param.getNumberParam();
            path = param.getStringParam();
            
            keyFactory factory;
            KeysGenerator & keyGen = factory;
            
            editor editor1(path, mode);
            encryptionDES encDES(keyGen, mode);
            Encryption & enc = encDES;
            File & file = editor1;
            Contents & content = enc;
            
            while (file.isEnd()) {
                file.reading(blockLength);
                file.writing(content);
            }
            
            if (mode) cout << "file was encrypted" << endl;
            else cout << "file was decrypted" << endl;
         }
    } catch (string ex) {
        cout << ex << endl;
    }
    
    return 0;
}

