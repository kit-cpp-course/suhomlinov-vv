//
//  encryption.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once
#include "stdafx.hpp"
#include "Contents.hpp"
#include "Keys.hpp"

/*
 * Класс шифрования и дешифрования блока бит
 */

class encryption: public Contents {
    Keys & key; // ссылка на объект, через который можно получить необходимые ключи
    int mode; // режим: шифрование 1, дешифрование 0
public:
    /*
     * Конструктор
     * @params key - ссылка на объект абстрактного класса Ключ
     * @params mode - режим (шифрование/дешифрование)
     */
    encryption(Keys & key, const int & mode) : key(key), mode(mode) {}
    
    /*
     * Получает блок битов (в виде массива bool) и возвращает (де)зашифрованный массив данных
     */
    bool * genereteContent(bool *);
};


