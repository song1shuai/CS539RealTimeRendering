//
//  Texture2D.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/23/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Texture2D__
#define __CS539_SHUAI_SONG__Texture2D__

#include <iostream>
#include <string>
#include <OpenGL/gl3.h>
#include "SOIL.h"
#include "ITexture.h"
const float boardColor1[]= {1.0,1.0,1.0,1.0};
const float boardColor2[]={0.0f, 0.0f, 0.0f, 0.0f};

class Texture2D:public ITexture
{
private:
    int _width;
    int _height;
    int _unitIndex;                     // GL_TEXTURE0 ...
    int _format;                        // Texture format GL_RGBA,GL_RGB etc...
    
    GLenum _minfiler;
    GLenum _magfiler;
    GLenum _type;
    
    GLuint _texID;                      // Texture handler
    
    static std::map<int, GLenum> unitID;

    static int SystemUnitIndex;         // currrent texture index;
    unsigned char* _image;              // a point use for store image information.
    bool _hasImage;
    int _sytermFormat;

public:
    
    
    static  Texture2D *CreateNextUnit();
    static  void ReSetUnitIndex();
    GLuint _texUnit;
    ~Texture2D();
    Texture2D();
    Texture2D(int index);
    static int GetNextUnitIndex();
    bool Load(std::string fileName);
    void Bind();
    void Init();
    void SetFilter(GLenum min,GLenum mag);
    void AttachByFrameBuffer(int texUnit ,int width , int height ,int format ,int sytermFormat=GL_RGBA);
    
    int GetUnitIndex();
    GLuint GetID(){return _texID;};
    //reset the system texture unit
    static void ReSetSUnitIndex();
};

#endif /* defined(__CS539_SHUAI_SONG__Texture2D__) */
