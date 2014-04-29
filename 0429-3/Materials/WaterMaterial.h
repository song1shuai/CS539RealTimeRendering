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
  
public:
    
    Texture2D * _diffuse;
    Texture2D * _reflection;
    void Bind();
    void Init();
   // re
    WaterMaterial(std::string textureName);
    
};

#endif /* defined(__CS539_SHUAI_SONG__WaterMaterial__) */
