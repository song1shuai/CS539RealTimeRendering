//
//  CubeTexture.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/24/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__CubeTexture__
#define __CS539_SHUAI_SONG__CubeTexture__

#include <iostream>
#include <list>
#include "ITexture.h"
#include <OpenGL/gl3.h>
#include "ITexture.h"
#include "SOIL.h"
#include<string>
class CubeTexture:public ITexture
{
    
    /*
     why i name i to cube texture , it should be called texture3d~~~
     */
    
private:
    
    unsigned char * _texture[6];
    GLuint _texID;
    int    _index;
    int    _size;
    bool   _hasImage;
    int    _unitIndex;
public:
    
    GLuint _texUnit;
    CubeTexture();
    virtual ~CubeTexture();

    bool Load(std::string fileName);
 
    virtual void Bind();
    virtual void Init();
    void AttachByFrameBuffer(int _size);
    int GetUnitIndex();
    int GetID();
    
};

#endif /* defined(__CS539_SHUAI_SONG__CubeTexture__) */
