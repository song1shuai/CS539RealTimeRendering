//
//  Mesh3DMaterial.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/8/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Mesh3DMaterial.h"
void Mesh3DMaterial::Bind()
{
    glEnable(GL_DEPTH_TEST);
    
    
    _shader->Bind();
    
    _shader->PushUniform("lightSPV",SceneManager::GetInstance().Getlight()->GetLightSPV());
    
    // Gl_texture_unit8 for shadowMap
    _shader->PushUniform("ShadowMap",SHADOWMAP_TEX_ID);
    //light
    _shader->PushUniform("lightPos",SceneManager::GetInstance().Getlight()->GetDirection());
    _shader->PushUniform("lightIntensity", SceneManager::GetInstance().Getlight()->GetIntensity());
    _shader->PushUniform("hasDecal", _hasTexture[MESHDECAL]);
    _shader->PushUniform("hasAlpha", _hasTexture[OPACITY]);
    
    for (int i = 0; i<4; i++)
    {
        if (_textures[i]!=NULL)
        {
            _textures[i]->Bind();
            switch (i)
            {
                case DIFFUSE:
                    _shader->PushUniform("texDiffuse",_textures[i]->GetUnitIndex());
                    break;
                case SPECULAR:
                    _shader->PushUniform("texAlpha", _textures[i]->GetUnitIndex());
                    break;
                case NORMAL:
                    _shader->PushUniform("texNormal", _textures[i]->GetUnitIndex());
                    break;
                case OPACITY:
                    _shader->PushUniform("texAlpha", _textures[i]->GetUnitIndex());
                    break;
                case MESHDECAL:
                    _shader->PushUniform("texDecal", _textures[i]->GetUnitIndex());
                    break;
                default:
                    //_textures[i]->Bind();
                    break;
            }
            
        }
    }
    
    
    
    
}
void Mesh3DMaterial::Init()
{
    
    for (int i = 0; i<4; i++)
    {
        if (_textures[i]!=NULL)
        {
            _textures[i]->Init();
        }
    }
    
}

void Mesh3DMaterial::SetDiff(Texture2D * diffuse)
{
    _hasTexture.Set(DIFFUSE, true);
    _textures[DIFFUSE]=diffuse;
}
void Mesh3DMaterial::SetSpec(Texture2D * specular)
{
    _hasTexture.Set(OPACITY, true);
    _textures[OPACITY]=specular;
}
void Mesh3DMaterial::SetNorml(Texture2D * normal)
{
    _hasTexture.Set(NORMAL, true);
    _textures[NORMAL]=normal;
}
void Mesh3DMaterial::SetAlpha(Texture2D * alpha)
{
    _hasTexture.Set(OPACITY, true);
    _textures[OPACITY]=alpha;
}

Mesh3DMaterial::Mesh3DMaterial():IMaterial("Mesh3D")
{
    _hasTexture.Reset();
    
    for (int i =0; i<5; i++)
    {
        _textures[i]=NULL;
    }
    
    Texture2D::ReSetSUnitIndex();
    
}
Mesh3DMaterial::~Mesh3DMaterial()
{
    
    
    for (int i = 0; i<4; i++)
    {
        if (_textures[i]!=NULL)
        {
            delete _textures[i];
        }
    }
    
}
void Mesh3DMaterial::UnBind()
{
    _shader->UnBind();
}
Texture2D * Mesh3DMaterial::GetTexture(TextureType type)
{
    return _textures[type];
}
void Mesh3DMaterial::SetDecal(Texture2D * decal)
{
    _hasTexture.Set(MESHDECAL, true);
    
    _textures[MESHDECAL]=decal;
}
void Mesh3DMaterial::SetTexture(TextureType type,Texture2D* texture)
{
    _hasTexture.Set(type, true);
    _textures[type]=texture;
}
void Mesh3DMaterial::SetTexture(TextureType type,string path)
{
    _hasTexture.Set(type, true);
    _textures[type]=Texture2D::CreateNextUnit();
    _textures[type]->Load(path);
    
}
