//
//  WaterMaterial.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/18/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "WaterMaterial.h"
void WaterMaterial::Bind()
{
    _shader ->Bind();
    _diffuse->Bind();
    _shader ->PushUniform("lightPos",SceneManager::GetInstance().Getlight()->GetDirection());
    _shader ->PushUniform("lightIntensity", SceneManager::GetInstance().Getlight()->GetIntensity());
    _shader ->PushUniform("cubeSampler", 0);
    _shader ->PushUniform("cameraPos",  SceneManager::GetInstance().GetCamera()->GetPosition());
    
}
void WaterMaterial::Init()
{
    _diffuse->Init();
}
WaterMaterial::WaterMaterial(std::string textureName):IMaterial("water")
{
     Texture2D::ReSetSUnitIndex();
    _diffuse = Texture2D::CreateNextUnit();
    _diffuse->Load(textureName);
    
}