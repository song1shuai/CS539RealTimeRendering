//
//  DirectionLight.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/11/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__DirectionLight__
#define __CS539_SHUAI_SONG__DirectionLight__

#include <iostream>
#include "IMaterial.h"
#include "GeomertryFactory.h"
#include "IDrawable.h"
#include "ILight.h"
#include "ITickable.h"
class GeomertryFactory;
class DirectionLight:public ITickable
{
private:
    

    
    glm::vec3 _intensity;
    glm::vec3 _direction;    //The deirction of the light
    
    glm::mat4 _view;        // The view matrix of the light
    glm::mat4 _proj;        // The projection matrix of the light
    glm::mat4 _pv;
    glm::mat4 _B;           // The  bais matrix

    IDrawable * cube;
    
    void Update();          // update Day night
    
public:
 
    static glm::mat4 BiasMatrix;
    DirectionLight();
    
    const glm::vec3& GetIntensity();
    const glm::vec3& GetDirection();
     glm::mat4 GetLightPV();
     glm::mat4 GetLightSPV();
  
    void SetDirection(float x ,float y,float z);
    
    virtual void ApplyLight(IMaterial *material);
    
    
    void Tick(float dt);
    
    
    
};
#endif /* defined(__CS539_SHUAI_SONG__DirectionLight__) */
