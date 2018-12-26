//
//  encryption.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "encryptionDES.hpp"
#include "feistel.hpp"
#include "stdafx.hpp"
#include "cryptlib.hpp"

/*
 * Переводит масссив символов в биты (bool)
 * @params symbols - массив символов
 * @params size - число битов
 */
char * convertToBits(const char * const symbols, int size);

/*
 * Переводит масссив битов (bool) в символы (char)
 * @params bites - массив битов
 * @params size - число битов
 */
char * convertToChar(const char * const bites, int size);

/*
* Переставляет элементы исходного блока согласно таблице
* @params text - блок битов
* @params table - таблица перестановок
* @params size - размер блока
*/
void makeBlockTransformation(char * text, const char * table, int size);

char * encryptionDES::encrypt(char * text) {
    return decrypt(text);
}

char * encryptionDES::decrypt(char * text) {
    feistel f(mode);
    char * newtext = new char[block];
    
    memcpy(newtext, convertToBits(text, block), block);
    makeBlockTransformation(newtext, initialTable, block);
    f.feistelCycle(newtext, keyGen);
    makeBlockTransformation(newtext, lastTable, block);
    
    return convertToChar(newtext, block);
}

char * encryptionDES::genereteContent(char * text) {
    if (mode) {
        return encrypt(text);
    } else {
        return decrypt(text);
    }
}

void makeBlockTransformation(char * text, const char * table, int size) {
    char * newtext = new char[size];
    for (int i = 0; i < size; i++) {
        newtext[i] = text[table[i] - 1];
    }
    memcpy(text, newtext, size);
}

char * convertToBits(const char * const symbols, int size) {
    char * bits = new char[size];
    for (int i = 0; i < size; i++) {
        bits[i] = (symbols[i / 8] >> (i % 8)) & 1;
    }
    return bits;
}

char * convertToChar(const char *  const bites, int size) {
    char * letters = new char[size / 8];
    memset(letters, 0, (size + 7) / 8);
    
    for (int i = 0; i < size; i++) {
        letters[i/8] |= bites[i] << (i % 8);
    }
    return letters;
}
