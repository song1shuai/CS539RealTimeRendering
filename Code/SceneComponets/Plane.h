//
//  Plane.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/12/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Plane__
#define __CS539_SHUAI_SONG__Plane__

#include <iostream>
#include "IDrawable.h"
#include "ITickable.h"
#include "IGeometry.h"
#include <vector>

class Plane:public IDrawable
{
private:
    float _xsize;
    float _zsize;
    int   _xdivs;
    int   _zdivs;
    float _smax;
    float _tmax;
    int faces;
public:
    Plane(const Plane & plane);
    Plane(float size, int xdivs=1, int zdivs=1, float smax=1.0, float tmax=1.0);
    virtual void Draw();
    virtual void InitVAO();
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
};
#endif /* defined(__CS539_SHUAI_SONG__Plane__) */
