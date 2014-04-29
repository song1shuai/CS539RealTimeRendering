//
//  ILight.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/12/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_ILight_h
#define CS539_SHUAI_SONG_ILight_h
#include "IMaterial.h"
#include "glm.hpp"
enum LightType
{
    DIRECTION,
    POINT,
    SPOTLIGHT
};

class ILight
{
private:
    LightType _type;
public:
    
   
    ILight(LightType type):_type(type){};
    virtual void ApplyLight(IMaterial *material)=0;
    LightType GetLightType()
    {
        return _type;
    }
};




#endif
