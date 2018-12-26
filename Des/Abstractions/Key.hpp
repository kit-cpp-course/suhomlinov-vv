//
//  Key.hpp
//  Des
//
//  Created by Виталий on 26.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once

/*
 * Абстракный класс, описывающий ключ
 */

class Key {
    
public:
    
    /*
     * Возвращает двоичный ключ
     */
    virtual char * getKey() = 0;
};
