//
//  keyFactory.hpp
//  Des
//
//  Created by Виталий on 26.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once
#include "KeysGenerator.hpp"
#include "Key.hpp"
#include "cryptlib.hpp"
#include "keyDES.hpp"

/*
 * Класс описывает фабрику ключей для шифрования DES
 */

class keyFactory: public KeysGenerator {
    Key * fkeys[16]; // Ключи шифрования Фейстеля (необходимы для 16 циклов шифрования)
    char * mainKey; // Ключ шифрования в двоичном виде
    
    /*
     * Генерирует ключи Фейстеля и добавляет их в fkeys
     * @params k - изначальный ключ шифрования (mainkey)
     */
    char * generateFeistelKey(char * key, int i);
    
    /*
     * Копирует ключ и возвращает на него указатель
     * @params k - изначальный ключ (mainkey)
     */
    Key * copyCurrentKey(char * k);
    
public:
    /*
     * Конструктор
     */
    keyFactory();
    
    /*
     * Деструктор
     */
    ~keyFactory();
    
    /*
     * Возвращает сгенерированный ключ по номеру
     * @params i - номер ключа
     */
    Key * generateKey(int i);
};
