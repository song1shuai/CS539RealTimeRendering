//
//  ICamera.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__ICamera__
#define __CS539_SHUAI_SONG__ICamera__

#include <iostream>
#include "glm.hpp"
#include "SceneNode.h"
class ICamera
{
protected:
   
public:
    SceneNode cameraNode;
    virtual glm::mat4 GetViewMatrix()=0;
    virtual glm::mat4 GetViewProjectionMatrix()=0;
    virtual glm::mat4 GetProjectionMatrix()=0;
    virtual glm::vec3 GetPosition()=0;
    virtual glm::vec3 GetForwardVector()=0;
    virtual glm::vec3 GetUp()=0;
    virtual glm::vec3 GetRight()=0;
    virtual void SetViewMatrix(glm::mat4 view)=0;
    virtual glm::mat4 GetCameraWorld()=0;
    //virtual glm::vec3 &GetPosition()=0;
//    {
//        return _position;
//    }

};
#endif /* defined(__CS539_SHUAI_SONG__ICamera__) */
