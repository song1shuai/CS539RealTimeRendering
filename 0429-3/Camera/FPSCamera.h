//
//  FPSCamera.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/13/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__FPSCamera__
#define __CS539_SHUAI_SONG__FPSCamera__
#include <iostream>
#include "SceneNode.h"
#include "glm.hpp"
#include "IInputListener.h"
#include "ICamera.h"
#include "SceneNode.h"
#include "ITickable.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>
enum CameraType {
	ORTHO, FREE
};
enum CameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK
};
class FPSCamera:public  IkeyBoardListener,public ICamera,public ITickable
{
private:
    /*
     below is just same basic camera param
     */
    
    
    
    glm::mat4 _projectonMatrix;
    glm::mat4 _view;
    glm::vec3 _target;
    glm::vec3 _up;
    glm::mat4 _world;
    
    
    glm::vec3 _direction;
    glm::quat _qRotation;
    glm::vec3 _position;
    glm::mat4 _orentation;
    
    float _yaw;
    float _pitch;
    
    float _sensitivity;                     // The sensitiviy when use yaw and pitch the camera
    float _MoveSpeed;                       // The move speed of the camera
    
    int  _x;                                // The x value of the mouse in screen space
    int  _y;                                // The y value of the mouse in screen space
    
    bool _isDirt;
public:
    FPSCamera();
    virtual ~FPSCamera();
    
    glm::mat4 GetViewMatrix();              // return the current the view matrix
    glm::mat4 GetViewProjectionMatrix();    // return the current view projection matrix
    glm::mat4 GetProjectionMatrix();        // return the current projction matrix
    glm::mat4 GetCameraWorld();             // return the camera maxtix in world space
    
    void Roll ( float angle);
    void Yaw (  float angle);
    void Pitch ( float angle);
    void ZoomIn(float distance,float dt);
    void ZoomOut(float distance,float dt);
    void LookAt(glm::vec3 location);
    void SetPerspective(float fov, float ratio, float near, float far);
    void SetCameraPosition(float x,float y,float z);
    void MoveFoword(float distance);
    void MoveBackwoards(float distance);
    void TurnRight(float distance);
    void TurnLeft(float distance);
    virtual void Tick(float dt);
    void Update();
    void Onkeyboard(float dt);
    void SetPostion(float x,float y,float z);
    void MoveUp(float distance);
    void MoveDown(float distance);
    
    /*
        use for get vectors of current camera matrix
     */
     glm::vec3 GetForwardVector();
     glm::vec3 GetUp();
     glm::vec3 GetPosition();
     glm::vec3 GetRight();
    
    
    
    virtual void SetViewMatrix(glm::mat4 view);//The the veiw matirx
   
    
    
};

#endif /* defined(__CS539_SHUAI_SONG__FPSCamera__) */
