//
//  feistel.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once
#include "Keys.hpp"

/*
 * Класс, реализующий функцию Фейстеля
 */

class feistel {
    int mode; // режим работы функции (шифрование, дешифрование)
public:
    /*
     * Конструктор
     * @params mode - режим (шифрование/дешифрование)
     */
    feistel(const int & mode) : mode(mode) {}
    
    /*
     * Преобразует исходный блок 16 циклами преобразования Фейстеля
     * @params key - ссылка на объект абстрактного класса Ключ
     * @params block - входной блок для шифрования/дешифрования
     */
    void feistelCycle(bool * block, Keys & fkey) const;
};
