//
//  encryption.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once
#include "stdafx.hpp"
#include "KeysGenerator.hpp"
#include "Encryption.hpp"

/*
 * Класс шифрования и дешифрования блока бит
 */

class encryptionDES: public Encryption {
    KeysGenerator & keyGen; // ссылка на объект, через который можно получить необходимые ключи
    int mode; // режим: шифрование 1, дешифрование 0
    
    /*
     * Шифрует данные
     * @params text - незашифрованный текст
     */
    char * encrypt(char * text);
    
    /*
     * Дешифрует данные
     * @params text - зашифрованный текст
     */
    char * decrypt(char * text);
    
public:
    /*
     * Конструктор
     * @params key - ссылка на объект абстрактного класса Ключ
     * @params mode - режим (шифрование/дешифрование)
     */
    encryptionDES(KeysGenerator & keyGen, const int & mode) : keyGen(keyGen), mode(mode) {}
    
    /*
     * Получает блок битов (в виде массива bool) и возвращает (де)зашифрованный массив данных
     */
    char * genereteContent(char *);
};


