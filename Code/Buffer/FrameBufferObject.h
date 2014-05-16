//
//  FrameBufferObject.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/19/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__FrameBufferObject__
#define __CS539_SHUAI_SONG__FrameBufferObject__

#include <iostream>
#include "Texture2D.h"
class FrameBufferObject
{
private:
    
    GLuint _dB;                 //The handler for the depth
    GLuint _fB;                 //The handler for the frame
    int _width;
    int _height;
    bool _isStoreDepth;
    Texture2D * _texture;       //The texture bind to framebuffer

public:
    /*TODO:
     
     should not be hardcoding ~~~
     */
    
    FrameBufferObject():_dB(0),_fB(0),_width(500),_height(500),_isStoreDepth(true),_texture(NULL){};
    void Bind();
    void UnBind();
    virtual void Init();
    void ResetViewPort();   // Reset the view port
    void Clear();
    static float size;
};

#endif /* defined(__CS539_SHUAI_SONG__FrameBufferObject__) */
