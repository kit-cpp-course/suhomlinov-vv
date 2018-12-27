//
//  consoleParams.hpp
//  Des
//
//  Created by Виталий on 22.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//
#pragma once
#include "stdafx.hpp"

/*
 * Класс отвечает за обработку аргументов командной строки
 */

class params {
    int count;
    char ** args;

    /*
     * Проверка корректности введеного числа
     * @params i - номер аргумента
     * @params bottom - нижняя граница
     * @params high - верхняя граница
     */
    bool isRightNumber(int i, char bottom, char high) const;

    /*
     * Проверка существования файла
     * @params fname - путь файла
     */
    bool isFileExist() const;

public:
    /*
     * Конструктор
     */
    params(int count, char ** args) : count(count), args(args) {}

    /*
     * Проверяет правильность введенных параметров
     */
    bool isParamsCorrect();

    /*
     * Возвращает строку из параметров
     */
    std::string getStringParam() { return (std::string)args[2]; };

    /*
     * Возвращает число из параметров
     */
    int getNumberParam();
};
