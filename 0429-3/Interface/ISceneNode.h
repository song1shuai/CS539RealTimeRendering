//
//  ISceneNode.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__ISceneNode__
#define __CS539_SHUAI_SONG__ISceneNode__

#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include "glm.hpp"
#include"matrix_transform.hpp"
#include "Shader.h"
#include "ext.hpp"
#include "quaternion.hpp"
#include <list>

class ISceneNode
{
    
    // contain all the information the drawable object in the scene
protected:

    ISceneNode *            _parentNode;
    std::list<ISceneNode*> _childList;
    
    void updateMatrix();
public:
    ISceneNode(){};
    virtual ~ISceneNode(){};
    
    virtual glm::mat4 GetTransformMatrix()=0;

    virtual void SetRotation(float dX,float dY,float dZ)=0;
    virtual void SetPosition(const glm::vec3& pVec)=0;
    virtual void SetScale(const glm::vec3& sVec)=0;
   
    // void updateMatrix();
    
    void Rotate(const glm::vec3&rVec);
    virtual void RotateX(float rX)=0;
    virtual void RotateY(float rY)=0;
    virtual void RotateZ(float rZ)=0;
    
    virtual void Translate(const glm::vec3&Tvec)=0;
    virtual void TranslateX(float tX)=0;
    virtual void TranslateY(float tY)=0;
    virtual void TranslateZ(float tZ)=0;
    
    virtual  glm::vec3 &GetPosition()=0;


    
};

#endif /* defined(__CS539_SHUAI_SONG__ISceneNode__) */
