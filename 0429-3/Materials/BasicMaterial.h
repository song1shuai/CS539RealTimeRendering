//
//  BasicMaterial.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__BasicMaterial__
#define __CS539_SHUAI_SONG__BasicMaterial__

#include <iostream>
#include "IMaterial.h"
#include "glm.hpp"
#include "SceneManager.h"
#include "Engine.h"
class BasicMaterial:public IMaterial
{
private:
    
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;
    float _shininess;
    
public:
    virtual ~BasicMaterial();

    void SetAmbient(float f);
    void SetShininess(float f);
    void SetAmbient(float r, float g, float b);
    
    void SetDiffuse(float f);
    void SetDiffuse(float r, float g, float b);
    
    void SetSpecular(float f);
    void SetSpecular(float r, float g, float b);
    
    
    BasicMaterial(std::string shader):IMaterial(shader){};
        
    void Bind();
};

#endif /* defined(__CS539_SHUAI_SONG__BasicMaterial__) */
