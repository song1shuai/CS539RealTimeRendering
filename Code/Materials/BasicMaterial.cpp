//
//  BasicMaterial.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "BasicMaterial.h"


void BasicMaterial::Bind()
{
    _shader->Bind();
    _shader->PushUniform("model",SceneManager::GetInstance().GetWorldModelMatrix());
    _shader->PushUniform("view", SceneManager::GetInstance().GetWorldViewMatrix());
    _shader->PushUniform("projection", SceneManager::GetInstance().GetWorldProjMatrix());
    
    _shader->PushUniform("mvp", SceneManager::GetInstance().GetMVPMatrix());
    _shader->PushUniform("nv", SceneManager::GetInstance().GetNV());

    glm::mat4 view =SceneManager::GetInstance().GetWorldViewMatrix();
    glm::vec3 wlightpos = SceneManager::GetInstance().Getlight()->GetDirection();
    glm::vec3 elightpos=glm::vec3(view * glm::vec4(wlightpos,0.0));
    
    _shader->PushUniform("lightPos",elightpos);
    _shader->PushUniform("lightIntensity", SceneManager::GetInstance().Getlight()->GetIntensity());
    
    
}

void BasicMaterial::SetShininess(float shininess)
{
 
    _shininess=shininess;
}
void BasicMaterial::SetAmbient(float f)
{
    _ambient.x=f;
    _ambient.y=f;
    _ambient.z=f;
}
void BasicMaterial::SetAmbient(float r, float g, float b)
{
    _ambient.x=r;
    _ambient.y=g;
    _ambient.z=b;
    
}

void BasicMaterial::SetDiffuse(float f)
{
    _diffuse.x=f;
    _diffuse.y=f;
    _diffuse.z=f;
}
void BasicMaterial::SetDiffuse(float r, float g, float b)
{
    _diffuse.x=r;
    _diffuse.y=g;
    _diffuse.z=b;
}

void  BasicMaterial::SetSpecular(float f)
{
    _specular.x=f;
    _specular.y=f;
    _specular.z=f;
    
}
void BasicMaterial::SetSpecular(float r, float g, float b)
{
    _specular.x=r;
    _specular.y=g;
    _specular.z=b;
}

