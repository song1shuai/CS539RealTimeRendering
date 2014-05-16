//
//  Force.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/9/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Force__
#define __CS539_SHUAI_SONG__Force__

#include <iostream>
#include "IEffect.h"
class Force:public IEffect
{
 void updateParticles(std::list<Particle> &_particles,float dt);
};

#endif /* defined(__CS539_SHUAI_SONG__Force__) */
