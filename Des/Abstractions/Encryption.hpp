//
//  Encryption.hpp
//  Des
//
//  Created by Виталий on 27.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once
#include "Contents.hpp"

/*
 * Абстрактный класс, описывающий шифрование данных
 */

class Encryption: public Contents {
  
public:
    
    /*
     * Шифрует данные
     * @params text - незашифрованный текст
     */
    virtual char * encrypt(char * text) = 0;
    
    /*
     * Дешифрует данные
     * @params text - зашифрованный текст
     */
    virtual char * decrypt(char * text) = 0;
};
