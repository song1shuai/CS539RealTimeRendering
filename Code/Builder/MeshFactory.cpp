//
//  MeshFactory.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/9/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "MeshFactory.h"
MeshFactory * MeshFactory::_instance=NULL;
MeshFactory:: MeshFactory()
{
    Mesh3D * house= new RotateHouse();
    house->LoadFromFile("Resource/house_obj.obj");
    house->InitVAO();
    _meshMap["house"]=house;

    
    
    
    Mesh3D * bamboo= new Mesh3D();
    bamboo->LoadFromFile("Resource/bamboo.obj");
    bamboo->InitVAO();
    //bamboo->sceneNode.SetScale(glm::vec3(0.2,0.2,0.2));
    _meshMap["bamboo"]=bamboo;
    bamboo->GetMaterial()->SetShader("plant");
    bamboo->SetRenderTech(CASTSHADOW);
    bamboo->SetRenderTech(CASTALPHASHADOW);
    
    Mesh3D * hightree= new Mesh3D();
  
    hightree->LoadFromFile("Resource/hightree_obj.obj");
      hightree->GetMaterial()->SetShader("plant");
    hightree->InitVAO();
    hightree->sceneNode.SetScale(glm::vec3(0.5,0.5,0.5));
    hightree->SetRenderTech(CASTSHADOW);
    hightree->SetRenderTech(CASTALPHASHADOW);
    _meshMap["hightree"]=hightree;
    
    
    Mesh3D * grass1= new Mesh3D();
    
    grass1->LoadFromFile("Resource/groundpalm.obj");
    grass1->GetMaterial()->SetShader("plant");
    grass1->InitVAO();
    //grass1->sceneNode.SetScale(glm::vec3(0.2,0.1,0.2));
    grass1->SetRenderTech(CASTSHADOW);
    grass1->SetRenderTech(CASTALPHASHADOW);
    _meshMap["grass1"]=grass1;
  
    Mesh3D * palmtree= new Mesh3D();
    
    palmtree->LoadFromFile("Resource/palmtree.obj");
    palmtree->GetMaterial()->SetShader("plant");
    palmtree->InitVAO();
    //grass1->sceneNode.SetScale(glm::vec3(0.2,0.1,0.2));
    palmtree->SetRenderTech(CASTSHADOW);
    palmtree->SetRenderTech(CASTALPHASHADOW);
    _meshMap["palmtree"]=palmtree;
    
    Mesh3D * eagle= new RotateHouse();
    eagle->LoadFromFile("Resource/eagle/EAGLE_2.3DS");
    eagle->InitVAO();
    _meshMap["eagle"]=eagle;

}
Mesh3D *MeshFactory::GetMesh(std::string name)
{
    Mesh3D * mesh = _meshMap[name]->Clone();
    SceneManager::GetInstance().AddToScene(mesh);
    return mesh;
}
MeshFactory::~MeshFactory()
{
    _meshMap.clear();
}