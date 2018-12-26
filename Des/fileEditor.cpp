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
    writeInFile(content.genereteContent(read), wFile);
    delete [] read;
}

void editor::writeInFile(const char * const symbols, ofstream & f) {
    int i = 0;
    if (mode || size) for (int i = 0; i < blockLength; i++) f << symbols[i];
    else while (symbols[i]) f << symbols[i++]; // В случае расшифровки не записываем лишние нули
}

bool editor::isEnd() { return size; }

int getFileSize(const string & pathFile) {
    fstream file(pathFile, ios::in|ios::ate);
    return (int)file.tellg();
}



