//
//  Contents.hpp
//  Des
//
//  Created by Виталий on 19.12.18.
//  Copyright © 2018 vlad. All rights reserved.
//
#pragma once

/*
 * Абстрактный класс, описывающий контент (даннныe)
 */

class Contents {
    
public:
    
    /*
     * Генерирует новые данные на основе поступивших
     */
    virtual char * genereteContent(char *) = 0;
};
