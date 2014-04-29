//
//  FPSCamera.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/13/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "FPSCamera.h"
FPSCamera::FPSCamera()
{
    _up = glm::vec3(0, 1, 0);
    _qRotation =  glm::quat(1, 0, 0, 0);
    _position = glm::vec3(131.5,10,-94.5 );
    _target = glm::vec3(-1.0,10.0,-1.0);
    
    _sensitivity=0.1;
    _MoveSpeed=10;
    
    _yaw = 180;
    _pitch = -10;
    this->_projectonMatrix=glm::perspective(60.f,
                                            4.0f / 3.0f,
                                            0.1f,
                                            200.0f
                                            );
     SDL_SetRelativeMouseMode(SDL_TRUE);
    _isDirt = false;
     Update();
}
FPSCamera::~FPSCamera()
{

    
}

glm::mat4 FPSCamera::GetViewMatrix()
{
//    if (_isDirt)
//    {
      Update();
//    }
    

    
    return _view;
}
glm::mat4 FPSCamera::GetViewProjectionMatrix()
{
    return _projectonMatrix*_view;
}
glm::mat4 FPSCamera::GetProjectionMatrix()
{
    return _projectonMatrix;
}
void FPSCamera::Tick(float dt)
{
 
   //Update();
   Onkeyboard( dt);
    
    
    
    
}
void FPSCamera::Update()
{

//    glm:: quat qPitch =glm:: angleAxis(_pitch, glm::vec3(1.0,0.0,0.0));
//    glm:: quat qYaw =glm:: angleAxis(_yaw,glm::vec3(0.0,1.0,0.0));
//    
//    glm:: quat temp = qPitch*qYaw;
//    
//    _view= glm::toMat4(temp);
//    
//    _world = glm::inverse(_view);
//    glm::value_ptr(_world)[12] = _position.x;
//    glm::value_ptr(_world)[13] = _position.y;
//    glm::value_ptr(_world)[14] = _position.z;
//    
//    _view = glm::inverse(_world);

   // _isDirt =false;
    
    
    
    glm:: quat qPitch =glm:: angleAxis(_pitch, glm::vec3(1.0,0.0,0.0));
    glm:: quat qYaw =glm:: angleAxis(_yaw,glm::vec3(0.0,1.0,0.0));
    
    glm:: quat temp = qPitch*qYaw;
    
    _view= glm::toMat4(temp);
    
    _world = glm::inverse(_view);
    glm::value_ptr(_world)[12] = _position.x;
    glm::value_ptr(_world)[13] = _position.y;
    glm::value_ptr(_world)[14] = _position.z;
    
    _view = glm::inverse(_world);

    
}
void FPSCamera::Yaw ( float angle)
{
    _yaw+=angle;

}
void FPSCamera::Pitch ( float angle)
{
    _pitch+=angle;
    

}
void FPSCamera::MoveFoword(float distance)
{
    
    _position.x
    -=
    distance*(float)sin(glm::radians(this->_yaw));
    
    _position.z
    +=
    distance*(float)cos(glm::radians(this->_yaw));
    
}
void FPSCamera::MoveBackwoards(float distance)
{
    _position.x
    +=
    distance*(float)sin(glm::radians(this->_yaw));
    
    _position.z
    -=
    distance*(float)cos(glm::radians(this->_yaw));
    
}
void FPSCamera::TurnRight(float distance)
{
    _position.x
    -=
    distance*(float)sin(glm::radians(this->_yaw+90));
    
    _position.z
    +=
    distance*(float)cos(glm::radians(this->_yaw+90));
}

void FPSCamera::TurnLeft(float distance)
{
    _position.x
    -=
    distance*(float)sin(glm::radians(this->_yaw-90));
    
    _position.z
    +=
    distance*(float)cos(glm::radians(this->_yaw-90));
    
}
void FPSCamera::Onkeyboard(float dt)
{

    
    //if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
    //{
        SDL_GetRelativeMouseState(&_x, &_y);
        this->Yaw(_x*_sensitivity);
        this->Pitch(_y*_sensitivity);
        
    //}

    
    if (isKeyDown(SDL_SCANCODE_R))
    {
        //std::cout<<dt*_MoveSpeed<<std::endl;
        
        this->MoveUp(dt*_MoveSpeed);
    }
    else if (isKeyDown(SDL_SCANCODE_F))
    {
        
      
          this->MoveDown(dt*_MoveSpeed);
    }
    if (isKeyDown(SDL_SCANCODE_RIGHT))
    {
        this->Yaw(dt*_sensitivity);
    }
    
    else if (isKeyDown(SDL_SCANCODE_LEFT))
    {
        
        this->Yaw(-dt*_sensitivity);
        
    }
    
    if (isKeyDown(SDL_SCANCODE_W))
    {
        //std::cout<<dt*_MoveSpeed<<std::endl;
         MoveBackwoards(dt*this->_MoveSpeed);
        
       
    }
    else if (isKeyDown(SDL_SCANCODE_S))
    {
        
        MoveFoword(dt*this->_MoveSpeed);
    }
    if (isKeyDown(SDL_SCANCODE_D))
    {
        TurnLeft(dt*this->_MoveSpeed);
    }
    
    else if (isKeyDown(SDL_SCANCODE_A))
    {
        
        TurnRight(dt*this->_MoveSpeed);
        
    }
    if (isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
    
    if (isKeyDown(SDL_SCANCODE_Q))
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
}
void FPSCamera::SetPostion(float x,float y,float z)
{
    _position.x=x;
    _position.y=y;
    _position.z=z;
}
void FPSCamera::MoveUp(float distance)
{
    _position.y+=distance;
}
void FPSCamera::MoveDown(float distance)
{
    _position.y-=distance;
}
glm::vec3 FPSCamera::GetForwardVector()
{
    _world = glm::inverse(_view);
    float *matrix =  glm::value_ptr(_world);
    return glm::vec3(matrix[-8],matrix[-9],matrix[-10]);
}
glm::vec3 FPSCamera::GetUp()
{
    
    _world = glm::inverse(_view);
    float *matrix =  glm::value_ptr(_world);
    return glm::vec3(matrix[4],matrix[5],matrix[6]);
    
}
glm::vec3  FPSCamera::GetPosition()
{
    
    _world = glm::inverse(_view);
    float *matrix =  glm::value_ptr(_world);
    
    return glm::vec3(matrix[12],matrix[13],matrix[14]);
}
 glm::vec3 FPSCamera::GetRight()
{
    _world = glm::inverse(_view);
    float *matrix =  glm::value_ptr(_world);
    return glm::vec3(matrix[0],matrix[1],matrix[2]);
}
 void FPSCamera::SetViewMatrix(glm::mat4 view)
{
    _isDirt = true;
    _view=view;
}
glm::mat4 FPSCamera::GetCameraWorld()
{
    
    Update();
    return _world;
}