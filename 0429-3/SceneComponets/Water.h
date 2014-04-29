//
//  Water.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/18/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Water__
#define __CS539_SHUAI_SONG__Water__

#include <iostream>
#include "Water.h"
#include "Plane.h"
#include "IDrawable.h"
#include "WaterMaterial.h"
#include "ITickable.h"
#include "glm.hpp"
#include "ICamera.h"
#include "HelperFunc.h"
#include "BoundingBox.h"
class Water:public IDrawable,public ITickable
{
    

    
    struct WaveParameters
    {
        float speed;
        float amplitude;
        float wavelength;
        float steepness;

    };

    
    
private:
    float _tickTime;
    Plane _waterSurface;
    glm::mat4 _waterView;
    glm::mat4 _mirrorMat;
    ICamera * _camera;
    float _waterHeight;
    
    glm::vec2 _directions[4];
    WaveParameters  _waveParam[4];
    
    glm::vec4 _waveParamater[4];
    
    BoundingBox *_boundingBox;
public:
    void SetCamera(ICamera * camera);
    Water(float size, int xdivs, int zdivs, float smax, float tmax);
    void Draw();
    void InitVAO();
    void Tick(float dt);
    void RandomDirection();
    void GenWave();
    glm::mat4 GetReflectMatrix();
    virtual ~Water();
    
    
};

#endif /* defined(__CS539_SHUAI_SONG__Water__) */
