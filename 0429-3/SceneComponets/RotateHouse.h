//
//  RotateHouse.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/12/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__RotateHouse__
#define __CS539_SHUAI_SONG__RotateHouse__

#include <iostream>
#include"Mesh3D.h"
#include "ITickable.h"
class RotateHouse:public Mesh3D,public ITickable
{
    
public:
    void Tick(float dt)
    {
        this->sceneNode.RotateY(dt);
    }
    
};


#endif /* defined(__CS539_SHUAI_SONG__RotateHouse__) */
