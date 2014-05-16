//
//  WaterMaterial.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/18/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__WaterMaterial__
#define __CS539_SHUAI_SONG__WaterMaterial__

#include <iostream>
#include "IMaterial.h"
#include "Texture2D.h"
#include "SceneManager.h"
#include <string>
#include "HelperFunc.h"

class WaterMaterial:public IMaterial
{
   // Material use for water ~~~~
    
public:
    

    
    Texture2D * _diffuse;           // not used
    Texture2D * _reflection;        // not used for now i just reflect the skybox 
    void Bind();
    void Init();
    WaterMaterial(std::string textureName);
    
};

#endif /* defined(__CS539_SHUAI_SONG__WaterMaterial__) */
