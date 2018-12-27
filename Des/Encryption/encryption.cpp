//
//  encryption.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "encryption.hpp"
#include "feistel.hpp"
#include "stdafx.hpp"
#include "cryptlib.hpp"

const char initialTable[] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};
const char lastTable[] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};

/*
* Переставляет элементы исходного блока согласно таблице
* @params text - блок битов
* @params table - таблица перестановок
* @params size - размер блока
*/
void makeBlockTransformation(bool * text, const char * table, int size);

bool * encryption::genereteContent(bool * text) {
    feistel f(mode);
    bool * newtext = new bool[block];
    memcpy(newtext, text, block);

    makeBlockTransformation(newtext, initialTable, block);
    f.feistelCycle(newtext, key);
    makeBlockTransformation(newtext, lastTable, block);

    return newtext;
}

void makeBlockTransformation(bool * text, const char * table, int size) {
    bool * newtext = new bool[size];
    for (int i = 0; i < size; i++) newtext[i] = text[table[i] - 1];
        memcpy(text, newtext, size);
}
