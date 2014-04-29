//
//  Mesh3D.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/7/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Mesh3D__
#define __CS539_SHUAI_SONG__Mesh3D__

#include <iostream>
#include "IDrawable.h"
#include <string>
#include  "Importer.hpp"
#include "scene.h"
#include "glm.hpp"
#include "postprocess.h"
#include "Texture2D.h"
#include <vector>
#include "Mesh3DMaterial.h"
#include "BoundingBox.h"

//using namespace glm;


class Mesh3DUnit:public IDrawable
{
    friend class Mesh3D;
    friend class BoundingBox;
private:
    
    GLuint _vbo;
    GLuint _ibo;
    
    unsigned int _numIndices;
    unsigned int _materialIndex;
    std::vector<unsigned int> _indices;
    std::vector<Vertex> _vertices;
    
public:
    
     Mesh3DUnit();
    ~Mesh3DUnit();

    void InitVAO();
    void Draw();

};

class Mesh3D:public IDrawable,public ITickable
{

private:
   // aiScene _scene;
    

    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void ReadMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    float _tickTime;
public:
    
    
   // Mesh3D(const Mesh3D & target);
    Mesh3D()
    {
        this ->SetRenderTech(CASTSHADOW);
        this ->SetRenderTech(HASAABB);
    
    };
    ~Mesh3D();
    bool LoadFromFile(const std::string &source);
    virtual void Draw();
    virtual void InitVAO();
    
    std::vector<Mesh3DUnit> _units;
    std::vector<Texture2D*> _textures;
    std::vector<glm::vec3> _instancePos;
    
    BoundingBox *  _boundingBox;
    Mesh3D* Clone();
    void Tick(float dt);
    
    
};

#endif /* defined(__CS539_SHUAI_SONG__Mesh3D__) */
