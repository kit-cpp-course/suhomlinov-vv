//
//  keyFactory.cpp
//  Des
//
//  Created by Виталий on 26.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "keyFactory.hpp"
#include "Key.hpp"
#include "keyDES.hpp"
#include "stdafx.hpp"

using namespace std;

const char keyNumber[] = {'i','t','s','m','y','k','y'}; // ключ шифрования

/*
 * Переводит массив char в массив битов (bool)
 * @params bites - массив, куда записываются биты
 * @params text - массив символов
 * @params bits - число битов
 */
void charToBits(char * bites, const char * text, int bits);

/*
 * Переставляет элементы исходного ключа согласно таблице и записывает
 * результат в новый ключ
 * @params toKey - новый ключ
 * @params fromKey - исходный ключ
 * @params table - таблица перестановок
 * @params len - длина ключа
 */
void makeKeyMix(char * toKey, char * fromKey, const char * table, int len);
/*
 * Осуществляет циклический сдвиг ключа
 * @params key - ключ
 * @params len - длина ключа
 * @params shift - величина сдвига
 */

void cycleShift(char * key, int len, int shift);

Key * keyFactory::generateKey(int i) {
    return copyCurrentKey(fkeys[i]->getKey());
}

keyFactory::keyFactory() {
    mainKey = new char[keyLength];
    charToBits(mainKey, keyNumber, block);
    makeKeyMix(mainKey, mainKey, genKeyTable, keyLength);
    
    for (int i = 0; i < 16; i++) {
        fkeys[i] = copyCurrentKey(generateFeistelKey(mainKey, i));
    }
}

Key * keyFactory::copyCurrentKey(char * k) {
    keyDES temp(k, feistelLength);
    keyDES * main = new keyDES;
    main->setKey(temp.getKey(), feistelLength);
    return main;
}

char * keyFactory::generateFeistelKey(char * key, int i) {
    char * lkey = key, * rkey = key + keyLength / 2; // указатели на первый элемент
    char * newKey = new char[feistelLength];
    
    cycleShift(lkey,28,cyclicalShiftKey[i]);
    cycleShift(rkey,28,cyclicalShiftKey[i]);
    makeKeyMix(newKey, key, genKeyFeistel, feistelLength);
    
    return newKey;
}

keyFactory::~keyFactory() {
    delete [] mainKey;
}

void charToBits(char * bites, const char * text, int bits) {
    for(int i = 0; i < bits; i++) {
        bites[i] = (text[i/8] >> (i % 8)) & 1;
    }
}

void cycleShift(char * key, int len, int shift) {
    bool temp[block];
    memcpy(temp, key, shift);
    memcpy(key, key + shift, len - shift);
    memcpy(key + len - shift, temp, shift);
}

void makeKeyMix(char * toKey, char * fromKey, const char * table, int length) {
    bool * tmp = new bool[length];
    for(int i = 0;i < length; i++) {
        tmp[i] = fromKey[table[i] - 1];
    }
    memcpy(toKey, tmp, length);
}



