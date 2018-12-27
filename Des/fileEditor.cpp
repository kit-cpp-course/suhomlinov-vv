//
//  fileEditor.cpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#include "fileEditor.hpp"
#include "cryptlib.hpp"
#include "stdafx.hpp"
#include "Contents.hpp"

using namespace std;

const string extention = ".txt";

const string encrypt = "Enc";

const string decrypt = "Dec";

 /*
  * Возвращает размер файла
  * @params pathFile - путь файла
  */
int getFileSize(const string & pathFile);

/*
 * Переводит масссив символов в биты (bool)
 * @params symbols - массив символов
 * @params size - число битов
 */
bool * convertToBits(const char * const symbols, int size);

/*
 * Переводит масссив битов (bool) в символы (char)
 * @params bites - массив битов
 * @params size - число битов
 */
char * convertToChar(const bool * const bites, int size);

char * getEncryptedSymbols(Contents & content, char * readSymbols);

// Реализация функций

void editor::reading(int length) {
    read = new char[blockLength];
    rFile.read(read, blockLength);

    if (size >= length) { size -= blockLength; }
    else if (size < length && size) {
        for (int i = size; i < blockLength; i++) { read[i] = 0; } // В случае нечетного числа битов записываем в файл нули
        size = 0;
    }
}

editor::editor(const string & path, const int & mode) : mode(mode) {
    rFile.open(path, ios::in);
    getNewPath(path);
    wFile.open(newPath, ios::app);
    size = getFileSize(path);
}

void editor::getNewPath(const string path) {
    string newpath = path;
    newPath = (newpath.erase(newpath.length() - 4, newpath.length()));
    newPath = newPath + (mode ? encrypt : decrypt) + extention;
}

void editor::writing(Contents & content) {
    char * symbols;

    symbols = getEncryptedSymbols(content, read);
    writeInFile(symbols, wFile);

    delete [] read;
}

char * getEncryptedSymbols(Contents & content, char * readSymbols) {
    bool * bits, * cryptbits;

    bits = convertToBits(readSymbols, block);
    cryptbits = content.genereteContent(bits);

    return convertToChar(cryptbits, block);;
}

void editor::writeInFile(const char * const symbols, ofstream & f) {
    int i = 0;
    if (mode || size) for (int i = 0; i < blockLength; i++) f << symbols[i];
    else while (symbols[i]) f << symbols[i++]; // В случае расшифровки не записываем лишние нули
}

bool editor::isEnd() { return size; }

bool * convertToBits(const char * const symbols, int size) {
    bool * bits = new bool[size];
    for (int i = 0; i < size; i++)
        bits[i] = (symbols[i / 8] >> (i % 8)) & 1;
    return bits;
}

char * convertToChar(const bool *  const bites, int size) {
    char * letters = new char[size / 8];
    memset(letters, 0, (size + 7) / 8);

    for (int i = 0; i < size; i++) letters[i/8] |= bites[i] << (i % 8);
    return letters;
}

int getFileSize(const string & pathFile) {
    fstream file(pathFile, ios::in|ios::ate);
    return (int)file.tellg();
}
