//
//  OpenGLContext.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "OpenGLContext.h"
bool OpenGLContext::InitOpenGLContext(std::string programName)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout<<"Unable to initialize SDL";
        CleanUp();
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(
                        SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE
                        );

    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    if ((_mainwindow =SDL_CreateWindow("Asssigment 1",100,100,500,500,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN))==NULL)
	{

		std::cout<<"Unable to window ";
        return false;
        
        
	}
    
    _maincontext = SDL_GL_CreateContext(_mainwindow);
    SDL_GL_SetSwapInterval(1);
    
    fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    fprintf(stdout, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    return true;
}
void OpenGLContext::TestRender()
{
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
  SDL_GL_SwapWindow(_mainwindow);
    //SDL_Delay(2000);
}
void OpenGLContext::CleanUp()
{
    SDL_GL_DeleteContext(_maincontext);
    SDL_DestroyWindow(_mainwindow);
    SDL_Quit();
}
OpenGLContext::~OpenGLContext()
{
    CleanUp();
    
}
SDL_Window *OpenGLContext::GetRenderWindow()
{
    return _mainwindow;
}