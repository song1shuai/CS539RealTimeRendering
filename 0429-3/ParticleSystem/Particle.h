//
//  Particle.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/9/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Particle__
#define __CS539_SHUAI_SONG__Particle__

#include <iostream>
#include "IDrawable.h"
class Particle
{

public:
    IDrawable * drawable;
    float lifeSpan;
    Particle();
    
    
};
#endif /* defined(__CS539_SHUAI_SONG__Particle__) */
