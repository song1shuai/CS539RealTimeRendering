//
//  MeshFactory.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/9/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__MeshFactory__
#define __CS539_SHUAI_SONG__MeshFactory__

#include <iostream>
#include "Mesh3D.h"
#include <map>
#include "RotateHouse.h"
#include "SceneManager.h"
class MeshFactory
{
private:
    std::map<std::string ,Mesh3D * > _meshMap;
    static MeshFactory * _instance;
public:
    static MeshFactory*GetInstance()
    {
        if (_instance ==NULL)
        {
            _instance = new MeshFactory();
        }
        
        return _instance;
    }
    
    MeshFactory();
    Mesh3D *GetMesh(std::string name);
    ~MeshFactory();
};

#endif /* defined(__CS539_SHUAI_SONG__MeshFactory__) */
