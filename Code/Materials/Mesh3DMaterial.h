//
//  Mesh3DMaterial.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/8/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Mesh3DMaterial__
#define __CS539_SHUAI_SONG__Mesh3DMaterial__

#include <iostream>
#include "IMaterial.h"
#include "Texture2D.h"
#include <vector>
#include "Engine.h"
#include "BitArray.h"
enum TextureType
    {DIFFUSE=0,
     SPECULAR=1,
     OPACITY=2,
     NORMAL=3,
     MESHDECAL=4
};
class Mesh3DMaterial:public IMaterial
{
    
    // The material use for 3d mesh which contain five types texture
    
private:
    
    Texture2D * _textures[5];
    
    BitArray _hasTexture;       // use for querry is this materail has some kind of materail
    
public:
    
    
    void SetDiff(Texture2D * diffuse);
    void SetSpec(Texture2D * specular);
    void SetNorml(Texture2D * normal);
    void SetAlpha(Texture2D * alpha);
    void SetDecal(Texture2D * decal);
    
    Texture2D * GetTexture(TextureType type);
    
    void SetTexture(TextureType type,Texture2D* texture);
    void SetTexture(TextureType type,string path);
    
    
    
    Mesh3DMaterial();
   ~Mesh3DMaterial();
    
    
    void Bind();
    void Init();
    void UnBind();
    
    
};
#endif /* defined(__CS539_SHUAI_SONG__Mesh3DMaterial__) */
