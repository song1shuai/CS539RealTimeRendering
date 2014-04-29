//
//  SkyBox.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/24/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__SkyBox__
#define __CS539_SHUAI_SONG__SkyBox__

#include <iostream>
#include "SceneNode.h"
#include "SkyBoxMaterial.h"
#include "IDrawable.h"
#include "CubeTexture.h"
#include <OpenGL/gl3.h>
#include "ShaderLibrary.h"
#include "ICamera.h"
class SkyBox:public IDrawable
{
    friend class SceneManager;
private:
    ICamera * _camera;
public:
   
    virtual ~SkyBox();
    SkyBox(IMaterial *  skyMaterial):IDrawable(skyMaterial)
    {
    };
    void InitVAO();
    void Draw();
    
};
#endif /* defined(__CS539_SHUAI_SONG__SkyBox__) */
