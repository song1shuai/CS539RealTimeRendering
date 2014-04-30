//
//  FrameBuffer.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/19/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "ShadowBuffer.h"
float ShadowBuffer::size=2048;
std::map<int, GLenum> ShadowBuffer::frameUnitID=
{
    std::make_pair(0,GL_COLOR_ATTACHMENT0),
    std::make_pair(1,GL_COLOR_ATTACHMENT1),
    std::make_pair(2,GL_COLOR_ATTACHMENT2),
    std::make_pair(3,GL_COLOR_ATTACHMENT3),
    std::make_pair(4,GL_COLOR_ATTACHMENT4),
    std::make_pair(5,GL_COLOR_ATTACHMENT5),
    std::make_pair(6,GL_COLOR_ATTACHMENT6),
    std::make_pair(7,GL_COLOR_ATTACHMENT7),
    std::make_pair(8,GL_COLOR_ATTACHMENT8),
    std::make_pair(9,GL_COLOR_ATTACHMENT9),
    std::make_pair(10,GL_COLOR_ATTACHMENT10),
};
void ShadowBuffer::Bind()
{
    
    glBindFramebuffer(GL_FRAMEBUFFER, _fB);
    glDrawBuffers(1, drawBuffers);
}
void ShadowBuffer::UnBind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
}
void ShadowBuffer::Init()
{
    glGenFramebuffers(1, &_fB);
    glBindFramebuffer(GL_FRAMEBUFFER, _fB);
 
    GLfloat border[] = {1.0f, 0.0f,0.0f,0.0f };
    // The depth buffer texture
    glGenTextures(1, &_dB);
    glBindTexture(GL_TEXTURE_2D, _dB);
    
    //Set a null image to store frame.

	glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT32F,_width,_height,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    // Assign the depth buffer texture to texture channel 0
    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, _dB);
    
    //attach the image to the frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D,
                           _dB,                  // The texture handler
                           0);
    
    drawBuffers[0] = GL_NONE;
    glDrawBuffers(1, drawBuffers);
    
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if( result == GL_FRAMEBUFFER_COMPLETE) {
        printf("Shadowbuffer is complete.\n");
    } else
    {
        printf("Shadowbuffer is not complete.\n");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);

}
ShadowBuffer::ShadowBuffer()
{
    _fB = 0;
    _isStoreDepth=false;
    _width = ShadowBuffer::size;
    _height =ShadowBuffer::size;
    
    
}
void ShadowBuffer::ResetViewPort()
{
    glViewport(0, 0, _width, _height);
}
void ShadowBuffer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

