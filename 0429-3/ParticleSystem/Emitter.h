//
//  Emitter.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/9/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Emitter__
#define __CS539_SHUAI_SONG__Emitter__

#include <iostream>
#include "ITickable.h"
#include <list>
#include "Particle.h"
#include "IEffect.h"
class Emitter:public ITickable
{
private:
    
    std::list<Particle> _particleList;
    std::list<IEffect*> _effectList;
    std::list<IEffect*> _initEffectList;
    std::list<IEffect*>::iterator iter;
    
public:
    
    void Tick(float dt);
};
#endif /* defined(__CS539_SHUAI_SONG__Emitter__) */
