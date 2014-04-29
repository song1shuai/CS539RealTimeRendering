//
//  TerrainMaterial.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/1/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "TerrainMaterial.h"
void TerrainMaterial::Init()
{
    for (int i = 0; i<7; i++)
    {
        if (_terrain[i]!=NULL)
        {
            _terrain[i]->Init();
        }
    }
}
void TerrainMaterial::Bind()
{
     _shader->Bind();
    

    
    // Gl_texture_unit8 for shadowMap
    _shader->PushUniform("ShadowMap",SHADOWMAP_TEX_ID);
    //update light
    _shader->PushUniform("lightPos",SceneManager::GetInstance().Getlight()->GetDirection());
    _shader->PushUniform("lightIntensity", SceneManager::GetInstance().Getlight()->GetIntensity());
    
    _shader->PushUniform("lightSPV",SceneManager::GetInstance().Getlight()->GetLightSPV());
    
    
    for (int i = 0; i< 7; i++)
    {
        if (_terrain[i]!=NULL)
        {
            _terrain[i]->Bind();
            switch (i)
            {
                case LOW:
                _shader->PushUniform("texLow",_terrain[i]->GetUnitIndex());
                break;
                case MIDDLE:
                _shader->PushUniform("texMiddle", _terrain[i]->GetUnitIndex());
                break;
                case HEIGH:
                _shader->PushUniform("texHeigh", _terrain[i]->GetUnitIndex());
                break;
                case DECAL:
                _shader->PushUniform("texDecal", _terrain[i]->GetUnitIndex());
                break;
                case NORMALLOW:
                _shader->PushUniform("texNormalLow", _terrain[i]->GetUnitIndex());
                break;
                case NORMALMIDDLE:
                _shader->PushUniform("texNormalMiddle", _terrain[i]->GetUnitIndex());
                break;
                case NORMALHEIGH:
                _shader->PushUniform("texNormalHeigh", _terrain[i]->GetUnitIndex());
                break;
                default:
                break;
            }
            
        }
    }

}
void TerrainMaterial::SetTexture(TerrainMaterialType type,string filePath)
{
    Texture2D *texture =Texture2D::CreateNextUnit();
    texture->Load(filePath);
   _terrain[type] = texture;
    
}
TerrainMaterial::TerrainMaterial():IMaterial("terrain")
{
    for (int i = 0; i<7; i++)
    {
        _terrain[i]=NULL;
        
       
        
    }
   // Texture2D::ReSetSUnitIndex();
}