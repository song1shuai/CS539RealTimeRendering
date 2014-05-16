//
//  Fructum.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/1/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Fructum__
#define __CS539_SHUAI_SONG__Fructum__

#include <iostream>
#include "glm.hpp"
#include "BoundingBox.h"

class BoundingBox;
class FrustumPlane
{
public:
    
    
    /*
     This function will set the Plane equation coefficients for the Plane equation a*x + b*y + c*z = d.
     */
    
    float d;
    float a, b, c;
    glm::vec3 normal;
  
    void SetCofficients(float a, float b, float c, float d); //set  coefficient of the plane
    
    float Distance( const glm::vec3 & point );
    
};

class Fructum
{

private:
    
    
    enum Planes
    {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        NEAR,
        FAR
    };
    
    FrustumPlane _fPlanes[6];
    
public:
    
    
    Fructum();
    bool IsCulledAABB(const BoundingBox & aabb);
    void Update(const glm::mat4 &mvp);
    
    
};


#endif /* defined(__CS539_SHUAI_SONG__Fructum__) */
