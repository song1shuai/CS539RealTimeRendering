//
//  FrameBufferObject3D.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/21/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "FrameBufferObject3D.h"
void FrameBufferObject3D::Bind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fB);
    glDrawBuffer( GL_COLOR_ATTACHMENT0);
    
}
void FrameBufferObject3D::UnBind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    
}
void FrameBufferObject3D::Init()
{
    glGenFramebuffers(1, &_fB);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fB);
    // The depth buffer texture
    
    if(_isStoreDepth)
    {
        glGenRenderbuffers(1, &_dB);
        glBindRenderbuffer(GL_RENDERBUFFER, _dB);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _size, _size);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _dB);
    }
    
    
    //Bind to a cube texture (3d);
    
    
    _texture.AttachByFrameBuffer(_size);
    _texture.Init();
    _texture.Bind();
    
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                           _texture.GetID(), 0);
    
    
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    
    GLenum result = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
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

    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

}
void FrameBufferObject3D::ResetViewPort()
{
    glViewport(0, 0, _size,_size );
}
void FrameBufferObject3D::Clear()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void FrameBufferObject3D::SetCurrentFace(GLenum face)
{
    //The the current face which will be stone into this buffer
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, face, _texture.GetID(), 0);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _dB);
    
}