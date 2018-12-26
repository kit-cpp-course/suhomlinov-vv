//
//  File.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//
#pragma once
#include "stdafx.hpp"
#include "Contents.hpp"

/*
 * Абстрактный класс описывающий файл 
 */

class File {
    
public:
    /*
     * Чтение данных определенной длины
     * @params length - длина чтения
     */
    virtual void reading(int length) = 0;
    
    /*
     * Запись данных в файл
     */
    virtual void writing(Contents & content) = 0;
    
    /*
     * Определяет дошло ли чтение файла до конца
     */
    virtual bool isEnd() = 0;
    
};

