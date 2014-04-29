//
//  SkyBoxMaterial.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/3/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "SkyBoxMaterial.h"
void SkyBoxMaterial::Bind()
{
    _shader->Bind();
    cubeTexture.Bind();

    _shader->PushUniform("cubeSampler",cubeTexture.GetUnitIndex());
    
}
void SkyBoxMaterial::Init()
{
    cubeTexture.Init();
}