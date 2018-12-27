//
//  key.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "key.hpp"
#include "stdafx.hpp"
#include "cryptlib.hpp"

using namespace std;

const char keyNumber[] = {'i','t','s','m','y','k','y'};

const char cyclicalShiftKey[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

const char genKeyFeistel[] = {
    14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10, 23, 19, 12, 4,
    26, 8,  16, 7,  27, 20, 13, 2,  41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

const char genKeyTable[] = {
    57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27, 19, 11, 3,  60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12,  4
};

/*
 * Переводит массив char в массив битов (bool)
 * @params bites - массив, куда записываются биты
 * @params text - массив символов
 * @params bits - число битов
 */
void charToBits(bool * bites, const char * text, int bits);

/*
 * Переставляет элементы исходного ключа согласно таблице и записывает
 * результат в новый ключ
 * @params toKey - новый ключ
 * @params fromKey - исходный ключ
 * @params table - таблица перестановок
 * @params len - длина ключа
 */
void makeKeyMix(bool * toKey, bool * fromKey, const char * table, int len);
/*
 * Осуществляет циклический сдвиг ключа
 * @params key - ключ
 * @params len - длина ключа
 * @params shift - величина сдвига
 */

void cycleShift(bool * key, int len, int shift);

// Реализация функций

key::key() {
    charToBits(mainKey, keyNumber, block);
    makeKeyMix(mainKey, mainKey, genKeyTable, keyLength);
    generateFeistelKeys(mainKey);
}

void charToBits(bool * bites, const char * text, int bits) {
    for(int i = 0; i < bits; i++)
        bites[i] = (text[i/8] >> (i % 8)) & 1;
}

void key::generateFeistelKeys(bool * const key) {
    bool * lkey = key, * rkey = key + keyLength / 2; // указатели на первый элемент

    for(int i = 0; i < 16; i++) {
        cycleShift(lkey,28,cyclicalShiftKey[i]);
        cycleShift(rkey,28,cyclicalShiftKey[i]);
        makeKeyMix(fkeys[i], key, genKeyFeistel, feistelLength);
    }
}

void cycleShift(bool * key, int len, int shift) {
    bool temp[block];
    memcpy(temp, key, shift);
    memcpy(key, key + shift, len - shift);
    memcpy(key + len - shift, temp, shift);
}

void makeKeyMix(bool * toKey, bool * fromKey, const char * table, int length) {
    bool * tmp = new bool[length];
    for(int i = 0;i < length; i++) tmp[i] = fromKey[table[i] - 1];
    memcpy(toKey, tmp, length);
}

bool * key::copyKey(const bool * const key, short length) const {
    bool * finalKey = new bool[length];
    memcpy(finalKey, key, length);
    return finalKey;
}

bool * key::getFeistelKey(int i) {
    bool * temp = copyKey(fkeys[i], feistelLength);
    return temp;
}
