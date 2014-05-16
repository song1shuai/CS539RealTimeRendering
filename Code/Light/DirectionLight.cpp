//
//  DirectionLight.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/11/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "DirectionLight.h"
glm::mat4 DirectionLight::BiasMatrix = glm::mat4( glm::vec4(0.5f,0.0f,0.0f,0.0f),
                                         glm::vec4(0.0f,0.5f,0.0f,0.0f),
                                         glm::vec4(0.0f,0.0f,0.5f,0.0f),
                                         glm::vec4(0.5f,0.5f,0.5f,1.0f)
                                         );

DirectionLight::DirectionLight()
{
    SetDirection(-175,200,-200);
    _intensity=glm::vec3(1.0f,1.0f,1.0f);
    
    _proj = glm::perspective(90.0f, 1.0f, 100.0f, 700.0f);
    

    _B =  glm::mat4(
                     glm::vec4(0.5f,0.0f,0.0f,0.0f),
                     glm::vec4(0.0f,0.5f,0.0f,0.0f),
                     glm::vec4(0.0f,0.0f,0.5f,0.0f),
                     glm::vec4(0.5f,0.5f,.5f,1.0f)
                    
                    );
    
}
const glm::vec3& DirectionLight::GetIntensity()
{
    return _intensity;
}
const glm::vec3& DirectionLight::GetDirection()
{
    return _direction;
}

 glm::mat4 DirectionLight::GetLightPV()
{
    Update();
    
    return _pv;
}
void DirectionLight::SetDirection(float x ,float y,float z)
{
    
    _direction = glm::vec3(x,y,z);
     Update();

}
void DirectionLight::ApplyLight(IMaterial *material)
{
    
}
void DirectionLight::Tick(float dt)
{
  // _direction = glm::rotate(_direction, 1*dt, glm::vec3(1.0,0.0,0.0));
}
 glm::mat4 DirectionLight::GetLightSPV()
{
    Update();
    return _B * _pv;
}
void DirectionLight::Update()
{
    _view = glm::lookAt(_direction, glm::vec3(0,0,0), glm::vec3(0,1,0));
    _pv = _proj *  _view ;
}