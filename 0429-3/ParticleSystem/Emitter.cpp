//
//  Emitter.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/9/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Emitter.h"
void Emitter::Tick(float dt)
{
    for (iter=_effectList.begin();iter!=_effectList.end(); ++iter)
    {
       //(*iter)->updateParticles(_particleList, dt);
    }
}