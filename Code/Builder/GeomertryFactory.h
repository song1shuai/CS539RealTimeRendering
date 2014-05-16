//
//  GeomertryFactory.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/14/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__GeomertryFactory__
#define __CS539_SHUAI_SONG__GeomertryFactory__

#include <iostream>
#include "IDrawable.h"
#include "Plane.h"
#include "Cube.h"
enum GeomertryType
{
    PLANE,
    CUBE,
    
};
class GeomertryFactory
{
public:

    static IDrawable * GetGeomertry(GeomertryType type ,int size)
    {
        switch (type)
        {
            case PLANE:
            
                return new Plane(size);
                break;
            case CUBE:
                return new Cube(size);
                
            default:
                break;
        }
    }
};


#endif /* defined(__CS539_SHUAI_SONG__GeomertryFactory__) */
