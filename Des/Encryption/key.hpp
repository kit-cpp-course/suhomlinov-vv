//
//  key.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma  once
#include "cryptlib.hpp"
#include "Key.hpp"
#include <memory.h>
#include "keyFactory.hpp"

/*
 * Класс ключ шифрования DES
 * В данном классе хранится двоичное представление ключа, его длина
 */

class keyDES: public Key {
    friend class keyFactory;
    char * fkey; // битовое представление ключа
    int length; // длина ключа
    
    /*
     * Копирует ключ
     * @params key - ключ, данные корого будут копироваться
     * @params length - длина ключа
     */
    char * copyKey(const char * key, short length);
    
    /*
     * Устанавливает новое значение ключу ключ
     * @params k - ключ, данные корого будут копироваться
     * @params length - длина ключа
     */
    void setKey(char * k, int length);
    
public:
    /*
     * конструктор
     */
    keyDES(char * k = 0, int length = 0);
    
    /*
     * Возвращает двоичный ключ
     */
    char * getKey();
};

