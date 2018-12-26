//
//  fileEditor.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once
#include "File.hpp"
#include "stdafx.hpp"
#include "Contents.hpp"

class editor: public File {
    std::string newPath; // Путь к файлу без расширения
    int mode; // Режим чтения
    int size; // Размер файла
    std::fstream rFile; // Файл чтения
    std::ofstream wFile; // Файл записи
    char * read; // Прочтенные символы
    
    /*
     * Получает нувый путь к итоговому файлу
     */
    void getNewPath(const std::string);
    
    /*
     * Осуществляет непосредственную запись в файл символов в соответствии с режимом
     */
    void writeInFile(const char * const symbols, std::ofstream & f);
   
public:
    
    /*
     * Конструктор
     * @params path - путь файла
     * @params mode - режим (шифрование, дешифрование)
     * @params content - контент, который может использоваться для записи в файл
     */
    editor(const std::string & path, const int & mode);
    
    /*
     * Чтение файла
     */
    void reading(int length);
    
    /*
     * Запись в файл контента
     */
    void writing(Contents & content);
    
    /*
     * Определяет дошло ли чтение файла до конца
     */
    
    bool isEnd();
};


