//
//  Fructum.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/1/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Fructum.h"


void FrustumPlane::SetCofficients(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->normal = glm::vec3(a,b,c);
    float length = normal.length();
    
    
    // normalize the plane
    
    this->a = a /length;
    this->b = b/length;
    this->c = c/length;
    this->d = d/length;
    this->normal=glm::normalize(this->normal);
}

float FrustumPlane::Distance(  const glm::vec3 & point )
{
    return (a * point.x + b*point.y + c * point.z + d);
}

Fructum::Fructum()
{
    
}

bool Fructum::IsCulledAABB(const BoundingBox & aabb)
{
    glm::vec3 minPoint = aabb.PLowLeftFront;
    glm::vec3 maxPoint = aabb.PUpRightBack;
    //for each plane do ...
 
    bool result = false;
    for(int i = 0; i < 6; ++i)
    {
        glm::vec3  pos = minPoint;
        glm::vec3  neg = maxPoint;
        if (_fPlanes[i].normal.x > 0)
        {
            pos.x = maxPoint.x;
            neg.x = minPoint.x;
        }
        if (_fPlanes[i].normal.y > 0)
        {
            pos.y = maxPoint.y;
            neg.y = minPoint.y;
        }
        if (_fPlanes[i].normal.z > 0)
        {
            pos.z = maxPoint.z;
            neg.z = minPoint.z;
        }
        // is the positive vertex outside?
        if (_fPlanes[i].Distance(pos) < 0)
        {
            return true;
        }
        // is the negative vertex outside?
        else if (_fPlanes[i].Distance(neg) < 0)
            result = false; // intersection
    }
    return result;
    
    
    
}
void Fructum::Update(const glm::mat4 &viewProjection)
{
    

    float a, b, c, d;
    const float * vp = glm::value_ptr(viewProjection);
    
    a = vp[3] - vp[1];
    b = vp[7] - vp[5];
    c = vp[11] - vp[9];
    d = vp[15] - vp[13];
    _fPlanes[TOP].SetCofficients( a, b, c, d );
    
    a = vp[3] + vp[1];
    b = vp[7] + vp[5];
    c = vp[11] + vp[9];
    d = vp[15] + vp[13];
    _fPlanes[BOTTOM].SetCofficients( a, b, c, d );
    
    a = vp[3] + vp[0];
    b = vp[7] + vp[4];
    c = vp[11] + vp[8];
    d = vp[15] + vp[12];
    _fPlanes[LEFT].SetCofficients( a, b, c, d );
    
    a = vp[3] - vp[0];
    b = vp[7] - vp[4];
    c = vp[11] - vp[8];
    d = vp[15] - vp[12];
    _fPlanes[RIGHT].SetCofficients( a, b, c, d );
    
    a = vp[3] + vp[2];
    b = vp[7] + vp[6];
    c = vp[11] + vp[10];
    d = vp[15] + vp[14];
    _fPlanes[NEAR].SetCofficients( a, b, c, d );
    
    a = vp[3] - vp[2];
    b = vp[7] - vp[6];
    c = vp[11] - vp[10];
    d = vp[15] - vp[14];
    _fPlanes[FAR].SetCofficients( a, b, c, d );
}