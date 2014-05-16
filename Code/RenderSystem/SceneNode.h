//
//  SceneNode.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__SceneNode__
#define __CS539_SHUAI_SONG__SceneNode__

#include <iostream>
#include "ISceneNode.h"


class SceneNode:public ISceneNode
{
protected:
    
    bool        _isVisible;
    glm::mat4   _transformMat;
    glm::vec3   _rotation;
    glm::quat   _quatRotation;
    glm::vec3   _position;
    glm::vec3   _scale;
   
    
    //User for rotate

    void updateMatrix();
    
public:
    
    SceneNode();
    virtual ~SceneNode(){};
    
    
    virtual glm::mat4 GetTransformMatrix()
    {
        updateMatrix();
        return _transformMat;
    }
    
    void SetRotation(float dX,float dY,float dZ);
    void SetOrientation(glm::quat orientaion);
    
    void SetPosition(const glm::vec3& pVec);
    void SetScale(const glm::vec3& sVec);
    // void updateMatrix();
    
    void Rotate(const glm::vec3&rVec);
    
    // Rotate degree/
    void RotateX(float dX);
    void RotateY(float dY);
    void RotateZ(float dZ);
    
    
    void Translate(const glm::vec3&Tvec);
    void TranslateX(float tX);
    void TranslateY(float tY);
    void TranslateZ(float tZ);
    
    //Return the raidancc
    float GetYaw();
    float GetPitch();
    
    glm::vec3 &GetPosition();
    
};
#endif /* defined(__CS539_SHUAI_SONG__SceneNode__) */
