//
//  terrain.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/31/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__terrain__
#define __CS539_SHUAI_SONG__terrain__

#include <iostream>
#include "IDrawable.h"
#include <string>
#include <OpenGL/gl3.h>
#include "SOIL.h"
#include "glm.hpp"
#include <vector>
#include "Mesh3D.h"
#include "HelperFunc.h"
#include "MeshFactory.h"
class terrain:public IDrawable
{
    
    // a hight map based terrain . try to implement the lod ~~
private:

    int _width;
    int _height;
    int _vertexCount;
    int _indexCount;
    GLuint _vbo;
    GLuint _ibo;
    
    unsigned char* _image;
    
    std::vector<Vertex> _vertices;
    std::vector<Vertex> _heightMapData;
    std::vector< int> _indices;
    
    std::vector<glm::vec3> _plantPos;
    std::vector<Mesh3D *>  _plants;
    
public:
    
    
    inline int GetIndexCount()
    {
        return _indexCount;
    }
    terrain(){};
    terrain(int width ,int height):_width(width),_height(height){};
    void CalculateNormals();
    virtual void Draw();
    virtual void InitVAO();
    bool LoadHightMap(string name,int height);
    void GenPlant();
    
};



#endif /* defined(__CS539_SHUAI_SONG__terrain__) */
