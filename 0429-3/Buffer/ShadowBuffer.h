//
//  ShadowBuffer.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/19/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__ShadowBuffer__
#define __CS539_SHUAI_SONG__ShadowBuffer__

#include <iostream>
#include "Texture2D.h"
#include  <vector>
#include <OpenGL/gl3.h>
class ShadowBuffer
{
private:
    
    GLuint _dB;
    GLuint _fB;
    int _width;
    int _height;
    bool _isStoreDepth;
    
    static std::map<int, GLenum> frameUnitID;
    
    GLenum drawBuffers[1];
    
public:
    static float size;
    ShadowBuffer();
    void Bind();
    void UnBind();
    void Init();
    void ResetViewPort();
    void Clear();
};

#endif /* defined(__CS539_SHUAI_SONG__ShadowBuffer__) */
