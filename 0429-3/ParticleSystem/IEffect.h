//
//  IEeffect.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/9/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__IEeffect__
#define __CS539_SHUAI_SONG__IEeffect__

#include <iostream>
#include <list>
#include "Particle.h"
class IEffect
{
   virtual void updateParticles(std::list<Particle> &_particles,float dt)=0;
};
#endif /* defined(__CS539_SHUAI_SONG__IEeffect__) */
