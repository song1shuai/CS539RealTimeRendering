//
//  FrameBufferObject3D.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/21/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__FrameBufferObject3D__
#define __CS539_SHUAI_SONG__FrameBufferObject3D__

#include <iostream>
#include <OpenGL/gl3.h>
#include "CubeTexture.h"
class FrameBufferObject3D
{
    
private:
    
    GLuint _dB;             //The handler for the depth
    GLuint _fB;             //The handler for the frame
    int _size;
    bool _isStoreDepth;
    CubeTexture  _texture;  //The cube texture bind to the framebufferobject2d
    
public:
    FrameBufferObject3D():_dB(0),_fB(0),_size(0),_isStoreDepth(true){};
    void Bind();
    void UnBind();
    virtual void Init();
    void ResetViewPort();
    void Clear();
    void SetSize(int size)
    {
        _size=size;
    }
    void SetCurrentFace(GLenum face);
};

#endif /* defined(__CS539_SHUAI_SONG__FrameBufferObject3D__) */
