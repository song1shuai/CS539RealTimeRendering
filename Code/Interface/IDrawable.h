//
//  IDrawable.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_IDrawable_h
#define CS539_SHUAI_SONG_IDrawable_h
#include "IMaterial.h"
#include <OpenGL/gl3.h>
#include "SceneNode.h"
#include "BitArray.h"

struct Vertex
{
    glm::vec3 _pos;
    glm::vec2 _tex;
    glm::vec3 _normal;
    glm::vec3 _tangent;
    Vertex(){}
    Vertex(const glm::vec3 & pos,
           const glm::vec2 & tex,
           const glm::vec3 & normal,
           const glm::vec3 & tangent)
    {
        _pos    = pos;
        _tex    = tex;
        _normal = normal;
        _tangent = tangent;
    }
};

class BoundingBox;
enum BufferType
{
    VERTEXS=0,
    TEXTURES,
    POINTES,
    NORMALS,
    INDICES,
    COLORS,
};

enum RenderTech
{
    CASTSHADOW,
    CASTALPHASHADOW,
    REFELECT,
    HASAABB,
    REFLECTION,
    INSTACNEDRAW,
};

class IDrawable
{
protected:
    
    GLuint _vao;
    GLuint _vbo;
    GLuint _vbos[6];
    GLenum _primitiveType;
    IMaterial * _material;
    
    BitArray _Tech;
public:
    // The render location;
    
    SceneNode sceneNode;
    
    virtual void Draw()=0;
    
    virtual void InitVAO()=0;
    
    IDrawable(){};
    IDrawable(IMaterial * material)
    {
        _material=material;
        _primitiveType=GL_TRIANGLES;
        _vao=0;
        _vbo=0;
        
        
        
    }
    virtual void AttachMaterial(IMaterial * material)
    {
        _material=material;
        
    }
    virtual IMaterial* GetMaterial()
    {
        
        return _material;
    }
    void SetPrimitveType(GLenum primitiveType)
    {
        _primitiveType=primitiveType;
    }
    void SetRenderTech(RenderTech t)
    {
        _Tech.Set(t, true);
        
    }
    bool CheckRenderTech(RenderTech t)
    {
        return _Tech[t];
    }

    
};


#endif
