//
//  Itexture.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/24/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_Itexture_h
#define CS539_SHUAI_SONG_Itexture_h
#include <map>
#include <iostream>
#include <OpenGL/gl3.h>
class ITexture
{
protected:
    

public:
    
    virtual void Bind()=0;
    virtual void Init()=0;
    
    virtual ~ITexture(){};
};


#endif
