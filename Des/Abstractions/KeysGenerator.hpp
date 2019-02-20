//
//  Keys.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once
#include "Key.hpp"

/*
 * Абстрактный класс генератора ключей
 */

class KeysGenerator {
    
public:
    
    /*
     * Возвращает ключ по индексу
     * @params i - индекс
     */
    virtual Key * generateKey(int i) = 0;
};


