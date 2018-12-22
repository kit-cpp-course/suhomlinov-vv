//
//  feistel.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "feistel.hpp"
#include "cryptlib.hpp"
#include "Keys.hpp"
#include "stdafx.hpp"

const char eTable[] = {
    32,1, 2, 3, 4, 5,4, 5, 6, 7, 8, 9,8, 9, 10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1
};

const char pTable[] = {
    16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
};

const char s_box[blockLength][block]={
    //s1
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
    //s2
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
    //s3
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    //s4
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
    //s5
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
    //s6
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
    //s7
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
    //s8
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};

using namespace std;

/*
 * Переводит массив char в массив битов (bool)
 * @params block - массив, куда записываются биты
 * @params source - массив символов
 * @params bits - число битов
 */
void byteToBit(bool * block, const char * const source, int bits);

/*
 * Из исходного блока создает новый блок s-преобразованиями
 * @params fblock - новый блок битов
 * @params source - исходный массив битов
 */
void sFunction(bool * fblock, const bool * source);

/*
 * Функция Фейстеля
 * @params fblock - массив битов
 * @params fkey - ключ для преобразования Фейстеля
 */
void feistelFunction(bool * fblock, const bool * const fkey);

/*
 * Функция xor
 * @params first - массив, над которым используют операцию xor
 * @params second - второй массив битов
 * @params count - число битов
 */
void makeXor(bool * first, const bool * const second, int count);

/*
 * Переставляет элементы исходного блока согласно таблице
 * @params fblock - результат перестановок
 * @params sblock - исходный блок
 * @params isource - таблица перестановок
 * @params length - размер блока
 */
void epTransform(bool * fblock, const bool * const sblock, const char * const isource, int length);

/*
 * Преобразует левую и правую части исходного блока
 * @params firstBlock - указатель на начало блока
 * @params secondBlock - указатель на середину блока
 * @params fkey - ключ для преобразования Фейстеля
 * @params i - номер ключа
 */
void changeBlocks(bool * firstBlock, bool * secondBlock, Keys & fkey, int i);

void feistel::feistelCycle(bool * blockBite, Keys & fkey) const {
    bool * pLeftBlock = blockBite, * pRightBlock = blockBite + 32;
    
    if(mode) {
        for (int i = 0; i < 16; i++){ changeBlocks(pRightBlock, pLeftBlock, fkey, i); }
        
    } else
        for (int i = 15; i >= 0; i--) { changeBlocks(pLeftBlock, pRightBlock, fkey, i); }
}

void changeBlocks(bool * firstBlock, bool * secondBlock, Keys & fkey, int i) {
    bool * tempBlock = new bool[halfblock];
    
    memcpy(tempBlock,firstBlock,halfblock);
    feistelFunction(firstBlock,fkey.getFeistelKey(i));
    
    makeXor(firstBlock, secondBlock, halfblock);
    memcpy(secondBlock,tempBlock,halfblock);
}

void feistelFunction(bool * fblock, const bool * const fkey) {
    bool * extentionBlock = new bool[feistelLength];
    
    epTransform(extentionBlock, fblock, eTable, feistelLength);
    makeXor(extentionBlock, fkey, feistelLength);
    sFunction(fblock,extentionBlock);
    epTransform(fblock,fblock,pTable,halfblock);
}

void makeXor(bool * first, const bool * const second, int count) {
    for (int i = 0; i < count; i++) { first[i] ^= second[i]; }
}

void epTransform(bool * fblock, const bool * const sblock, const char * const isource, int length) {
    static bool tmp[block];
    for(int i = 0; i < length; i++) tmp[i] = sblock[isource[i] - 1];
    memcpy(fblock,tmp,length);
}

void sFunction(bool * fblock, const bool * source) {
    int first, second;
    
    for(char i=0;i < blockLength; i++, source+=6, fblock+=4)
    {
        first = (source[0] << 1) + source[5];
        second = (source[1] << 3) + (source[2] << 2) + (source[3] << 1) + source[4];
        byteToBit(fblock,&s_box[i][first * 16 + second],4);
    }
}

void byteToBit(bool * block, const char * const source, int bits) {
    for(int i = 0; i < bits; i++) { block[i] = ( source[i/8] >> (i % 8)) & 1; }
}
