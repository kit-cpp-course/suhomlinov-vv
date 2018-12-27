//
//  Keys.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//

#pragma once

/*
 * Абстрактный класс ключей
 */

class Keys {

public:

    /*
     * Возвращает ключ по индексу
     * @params i - индекс
     */
    virtual bool * getFeistelKey(int) = 0;
};
