//
//  Cube.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/14/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Cube__
#define __CS539_SHUAI_SONG__Cube__

#include <iostream>
#include "IDrawable.h"
#include "ITickable.h"
class Cube :public IDrawable,public ITickable
{
private:

    int _size;
    int _face;
    
public:
    
     Cube(int size):_size(size){};
    virtual void Draw();
    virtual void InitVAO();
    void Tick(float dt)
    {
        this->sceneNode.RotateY (dt*5);
    }
};

#endif /* defined(__CS539_SHUAI_SONG__Cube__) */
