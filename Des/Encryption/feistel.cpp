//
//  feistel.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "feistel.hpp"
#include "cryptlib.hpp"
#include "Key.hpp"
#include "KeysGenerator.hpp"
#include "stdafx.hpp"

using namespace std;

/*
 * Переводит массив char в массив битов (bool)
 * @params block - массив, куда записываются биты
 * @params source - массив символов
 * @params bits - число битов
 */
void byteToBit(char * block, const char * const source, int bits);

/*
 * Из исходного блока создает новый блок s-преобразованиями
 * @params fblock - новый блок битов
 * @params source - исходный массив битов
 */
void sFunction(char * fblock, const char * source);

/*
 * Функция Фейстеля
 * @params fblock - массив битов
 * @params fkey - ключ для преобразования Фейстеля
 */
void feistelFunction(char * fblock, const char * const fkey);

/*
 * Функция xor
 * @params first - массив, над которым используют операцию xor
 * @params second - второй массив битов
 * @params count - число битов
 */
void makeXor(char * first, const char * const second, int count);

/*
 * Переставляет элементы исходного блока согласно таблице
 * @params fblock - результат перестановок
 * @params sblock - исходный блок
 * @params isource - таблица перестановок
 * @params length - размер блока
 */
void epTransform(char * fblock, const char * const sblock, const char * const isource, int length);

/*
 * Преобразует левую и правую части исходного блока
 * @params firstBlock - указатель на начало блока
 * @params secondBlock - указатель на середину блока
 * @params fkey - ключ для преобразования Фейстеля
 * @params i - номер ключа
 */
void changeBlocks(char * firstBlock, char * secondBlock, Key * fkey, int i);

void feistel::feistelCycle(char * blockBite, KeysGenerator & fkey) const {
    char * pLeftBlock = blockBite, * pRightBlock = blockBite + 32;
    
    if(mode) {
        for (int i = 0; i < 16; i++){ changeBlocks(pRightBlock, pLeftBlock, fkey.generateKey(i), i); }
    } else {
        for (int i = 15; i >= 0; i--) { changeBlocks(pLeftBlock, pRightBlock, fkey.generateKey(i), i); }
    }
}

void changeBlocks(char * firstBlock, char * secondBlock, Key * fkey, int i) {
    char * tempBlock = new char[halfblock];
    
    memcpy(tempBlock,firstBlock,halfblock);
    feistelFunction(firstBlock,fkey->getKey());
    makeXor(firstBlock, secondBlock, halfblock);
    memcpy(secondBlock,tempBlock,halfblock);
}

void feistelFunction(char * fblock, const char * const fkey) {
    char * extentionBlock = new char[feistelLength];
    
    epTransform(extentionBlock, fblock, eTable, feistelLength);
    makeXor(extentionBlock, fkey, feistelLength);
    sFunction(fblock,extentionBlock);
    epTransform(fblock,fblock,pTable,halfblock);
}

void makeXor(char * first, const char * const second, int count) {
    for (int i = 0; i < count; i++) {
        first[i] ^= second[i];
    }
}

void epTransform(char * fblock, const char * const sblock, const char * const isource, int length) {
    static char tmp[block];
    for(int i = 0; i < length; i++) {
        tmp[i] = sblock[isource[i] - 1];
    }
    memcpy(fblock,tmp,length);
}

void sFunction(char * fblock, const char * source) {
    int first, second;
    
    for(char i=0;i < blockLength; i++, source+=6, fblock+=4) {
        first = (source[0] << 1) + source[5];
        second = (source[1] << 3) + (source[2] << 2) + (source[3] << 1) + source[4];
        byteToBit(fblock,&s_box[i][first * 16 + second],4);
    }
}

void byteToBit(char * block, const char * const source, int bits) {
    for(int i = 0; i < bits; i++) {
        block[i] = ( source[i/8] >> (i % 8)) & 1;
    }
}
