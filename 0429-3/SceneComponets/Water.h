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
    
// wate
    
    struct WaveParameters
    {
        float speed;
        float amplitude;
        float wavelength;
        float steepness;

    };

    
    
private:
    float _tickTime;
    Plane _waterSurface;                // a grid  use for generate flat water surface
    glm::mat4 _waterView;
    glm::mat4 _mirrorMat;               // the reflect matrix of from the water
    ICamera * _camera;                  // current camera
    float _waterHeight;                 // the high of the water
    
    glm::vec2 _directions[4];
    WaveParameters  _waveParam[4];
    
    glm::vec4 _waveParamater[4];
    
    
    // add the bounding box to the water so
    //i can check if a point is in the water when i randomly generate staff such as trees in the terrain
    BoundingBox *_boundingBox;
public:
    void SetCamera(ICamera * camera);
    Water(float size, int xdivs, int zdivs, float smax, float tmax);
    void Draw();
    void InitVAO();
    void Tick(float dt);
    void RandomDirection();         //random generate some  dirction of the water 
    void GenWave();
    glm::mat4 GetReflectMatrix();
    virtual ~Water();
    
    
};

#endif /* defined(__CS539_SHUAI_SONG__Water__) */
