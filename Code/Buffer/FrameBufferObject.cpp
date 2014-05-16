//
//  FrameBufferObject.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/19/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "FrameBufferObject.h"
float FrameBufferObject::size = 500;
void FrameBufferObject::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fB);
    glDrawBuffer( GL_COLOR_ATTACHMENT0);
}
void FrameBufferObject::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void FrameBufferObject::Init()
{
    glGenFramebuffers(1, &_fB);
    glBindFramebuffer(GL_FRAMEBUFFER, _fB);
    // The depth buffer texture
    
    if(_isStoreDepth)
    {// bind framebuffer to a renderbuffers
        
        glGenRenderbuffers(1, &_dB);
        glBindRenderbuffer(GL_RENDERBUFFER, _dB);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _dB);
    }
    
    //Bind framebuffer to a texture

        _texture = new Texture2D();
        _texture ->AttachByFrameBuffer(9,_width, _height, GL_RGBA);
        _texture->Init();
        _texture->Bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->GetID(), 0);

    
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
    
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    // debug the error message
    
    
    switch(result)
    {
        case GL_FRAMEBUFFER_COMPLETE:

            std::cout <<"CFrameBuffer: [SUCCESS] framebuffer object is complete...\n"<<std::endl;


            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:

            std::cout <<"CFrameBuffer: [ERROR] framebuffer incomplete, incomplete attachment...\n"<<std::endl;

            break;
            
        case GL_FRAMEBUFFER_UNSUPPORTED:

            std::cout <<"Unsupported framebuffer format...\n"<<std::endl;


            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:

            std::cout <<"CFrameBuffer: [ERROR] framebuffer incomplete, missing attachment...\n"<<std::endl;
            
            break;
            
        default:
            
            std::cout <<"CFrameBuffer: [ERROR] framebuffer incomplete. unknown reason.."<<std::endl;


    }


    glBindFramebuffer(GL_FRAMEBUFFER,0);


}
void FrameBufferObject::ResetViewPort()
{
    glViewport(0, 0, _width, _height);

}
void FrameBufferObject::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


