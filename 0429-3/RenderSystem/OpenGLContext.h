//
//  OpenGLContext.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__OpenGLContext__
#define __CS539_SHUAI_SONG__OpenGLContext__
#define GL3_PROTOTYPES 1
#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <stdio.h>
#include <stdlib.h>
class OpenGLContext
{
private:
 
    
    SDL_Window *_mainwindow; /* Our window handle */
    SDL_GLContext _maincontext;
   
    
public:
    SDL_Window *GetRenderWindow();
    OpenGLContext(){};
    ~OpenGLContext();
    bool InitOpenGLContext(std::string programName);
    void TestRender();
    void CleanUp();
    
};

#endif /* defined(__CS539_SHUAI_SONG__OpenGLContext__) */
