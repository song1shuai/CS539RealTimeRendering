//
//  HelperFunc.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/24/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "HelperFunc.h"
float Random1D(float min ,float max)
{
    float temp = (double) rand() / (double) RAND_MAX;
    float reslut = min + temp * (max - min);
    return reslut;
};

