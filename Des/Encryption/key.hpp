//
//  key.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma  once
#include "cryptlib.hpp"
#include "Keys.hpp"

/*
 * Класс ключ
 * В данном классе хранятся и генерируются ключи
 */


class key: public Keys {
    
    bool mainKey[block]; // Ключ шифрования в двоичном виде
    bool fkeys[16][feistelLength]; // Ключи шифрования Фейстеля (необходимы для 16 циклов шифрования)
    
    // Функции
    /*
     * Генерирует ключи Фейстеля и добавляет их в fkeys
     * @params k - изначальный ключ шифрования (mainkey)
     */
    
    void generateFeistelKeys(bool * const k);
    
    /*
     * Копирует ключ
     * @params k - какой-либо ключ шифрования
     * @params length - длина ключа
     */
    
    bool * copyKey(const bool * const k, short length) const;
    
public:
    /*
     * конструктор
     */
    key();
    
    /*
     * Возвращает определенный ключ Фейстеля из fkeys
     * @params i - индекс ключа
     */
    
    bool * getFeistelKey(int i);
    
};

