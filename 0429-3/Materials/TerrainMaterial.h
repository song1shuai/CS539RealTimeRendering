//
//  TerrainMaterial.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/1/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__TerrainMaterial__
#define __CS539_SHUAI_SONG__TerrainMaterial__

#include <iostream>
#include "IMaterial.h"
#include "Texture2D.h"
#include "Engine.h"
enum TerrainMaterialType
{
    LOW=0,
    MIDDLE=1,
    HEIGH=2,
    DECAL=3,
    NORMALLOW=4,
    NORMALMIDDLE=5,
    NORMALHEIGH=6
};
class TerrainMaterial:public IMaterial
{
private:
    Texture2D * _terrain[7];
public:
    
    TerrainMaterial();
    void SetTexture(TerrainMaterialType type,string filePath);
    virtual void Init();
    virtual void Bind();
    
};
#endif /* defined(__CS539_SHUAI_SONG__TerrainMaterial__) */
