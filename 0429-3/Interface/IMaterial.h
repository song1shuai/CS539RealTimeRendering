//
//  IMaterial.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_IMaterial_h
#define CS539_SHUAI_SONG_IMaterial_h
#include "Shader.h"
#include <string>
#include "ShaderLibrary.h"
#include  <map>
#include <OpenGL/gl3.h>
#define  DEPTHUNITINDEX 10
#define  ENVIRMENTUINTINDEX 11
#define  REFLECTIONUINITINDEX 9

class IMaterial
{
    

public:
   
    IMaterial(std::string shaderName)
    {
        _shader=ShaderLibrary::GetShader(shaderName);
    }

    virtual Shader* GetShader()
    {
        return _shader;
    }
    void SetShader(std::string shaderName)
    {
         _shader=ShaderLibrary::GetShader(shaderName);
    }
    void AttachShader(std::string shaderName)
    {
        _shader=ShaderLibrary::GetShader(shaderName);
    }
    
    
    virtual void Init()=0;
    virtual void Bind()=0;
    virtual ~IMaterial(){};
    virtual void UnBind(){};
protected:
    Shader* _shader;
};


#endif
