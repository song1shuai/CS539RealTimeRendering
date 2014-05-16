//
//  SceneNode.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "SceneNode.h"
SceneNode::SceneNode()
{
    _transformMat=glm::mat4(1.0);
    
    _rotation=glm::vec3(0.0);
    _scale=glm::vec3(1.0);
    _position=glm::vec3(0.0);
    
}
//
void SceneNode::SetRotation(float dX,float dY,float dZ)
{/*
    render the 
  */
    
    _rotation.x=glm::radians(dX);
    _rotation.y=glm::radians(dY);
    _rotation.z=glm::radians(dZ);
}
void SceneNode::SetOrientation(glm::quat orientaion)
{
    _quatRotation=orientaion;
}
void SceneNode::SetPosition(const glm::vec3& pVec)
{
    _position=pVec;
}
void SceneNode::SetScale(const glm::vec3& sVec)
{
    _scale=sVec;
}
void SceneNode::updateMatrix()
{

    _transformMat=glm::mat4(1.0);
    
    
    _quatRotation=glm::quat(_rotation);    
    glm::mat4 translateMat=glm::translate( _position);
    glm::mat4 scalMat= glm::scale( _scale);
    glm::mat4 rotateMat=glm::toMat4(_quatRotation);
    _transformMat =translateMat*rotateMat*scalMat;
    

}

void SceneNode::Rotate(const glm::vec3&rVec)
{
    
}
void SceneNode::RotateX(float dX)
{
    _rotation.x+=glm::radians(dX);

}
void SceneNode::RotateY(float dY)
{
    _rotation.y+=glm::radians(dY);
}
void SceneNode::RotateZ(float dZ)
{
   
    _rotation.z+=glm::radians(dZ);

}

void SceneNode::Translate(const glm::vec3&Tvec)
{
    _position+=Tvec;
    updateMatrix();
}
void SceneNode::TranslateX(float tX)
{
    _position.x+=tX;
    updateMatrix();
}
void SceneNode::TranslateY(float tY)
{
    _position+=tY;
     updateMatrix();
}
void SceneNode::TranslateZ(float tZ)
{
    _position+=tZ;
     updateMatrix();
}
float SceneNode::GetYaw()
{
    return _rotation.y;
}
float SceneNode::GetPitch()
{
    return _rotation.x;
}
glm::vec3 &SceneNode::GetPosition()
{
    return _position;
}