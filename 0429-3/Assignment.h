//
//  Assignment.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Assignment__
#define __CS539_SHUAI_SONG__Assignment__

#include <iostream>
#include "SceneManager.h"
#include"OpenGLContext.h"
#include "SOIL.h"
#include "SkyBox.h"
#include "InputHandler.h"
#include "SceneNode.h"
#include "ShaderLibrary.h"
#include "Materials/BasicMaterial.h"
#include "CubeTexture.h"
#include "Mesh3D.h"
#include "RotateHouse.h"
#include "Plane.h"
#include "FPSCamera.h"
#include "Cube.h"
#include "Terrain.h"
#include "TerrainMaterial.h"
#include "Fructum.h"
#include "MeshFactory.h"
#include "Water.h"
#include "sound.h"
class Assignment
{
    
private:
    
    OpenGLContext _opengGLcontext;              
    InputHandler _inputhandler;
    sound _sound;
    
    SkyBox *skyBox;
    FPSCamera * _camera;
    
    float   _FPS;
    int     _lasTime;
    int     _currentTime;
    
public:
    
    Assignment();
    ~Assignment();
    void Render();
    void Run();
    
};
#endif /* defined(__CS539_SHUAI_SONG__Assignment__) */
