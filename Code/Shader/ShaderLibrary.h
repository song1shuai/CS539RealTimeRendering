//
//  ShaderLibrary.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__ShaderLibrary__
#define __CS539_SHUAI_SONG__ShaderLibrary__

#include <iostream>
#include "Shader.h"
#include <assert.h>
class ShaderLibrary
{

private:
    
    static map<string, Shader*> shaders;
    static map<string, Shader*>::iterator iter;
    
public:
    ~ShaderLibrary();
    static Shader* GetShader(string name);
    static void AddShader(Shader*);
    static void ClearUp();
    static void Init();
    
};

#endif /* defined(__CS539_SHUAI_SONG__ShaderLibrary__) */
