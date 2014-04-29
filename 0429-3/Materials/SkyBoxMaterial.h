//
//  SkyBoxMaterial.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/3/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__SkyBoxMaterial__
#define __CS539_SHUAI_SONG__SkyBoxMaterial__

#include <iostream>
#include "IMaterial.h"
#include "CubeTexture.h"
#include "SceneManager.h"
class SkyBoxMaterial:public IMaterial
{

    
public:
    CubeTexture cubeTexture;
    
    SkyBoxMaterial():IMaterial("skyBox")
    {
 
    };
    void Bind();
    virtual void Init();
};

#endif /* defined(__CS539_SHUAI_SONG__SkyBoxMaterial__) */
