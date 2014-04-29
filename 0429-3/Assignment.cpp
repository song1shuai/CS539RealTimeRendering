//
//  Assignment.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Assignment.h"
Assignment::Assignment()
{
    _FPS=60;
    
    _opengGLcontext.InitOpenGLContext("test");
    
    //OpenGLContext *O;
    SceneManager::GetInstance().SetOpenGLContext(&_opengGLcontext);
    
    
    //Init sceneManager
    SceneManager::GetInstance().Init();
    
    
    //Init shader
    ShaderLibrary::Init();
    
    
    //Add camera to the scene
    _camera  =new FPSCamera();
    SceneManager::GetInstance().SetCamera(_camera);
    SceneManager::GetInstance().AddToTickable(_camera);
    
    //Add skybox to the scene
    SkyBoxMaterial* skyboxM=new SkyBoxMaterial();
    skyboxM->cubeTexture.Load("px_.jpg");
    skyboxM->cubeTexture.Load("nx_.jpg");
    skyboxM->cubeTexture.Load("ny_.jpg");
    skyboxM->cubeTexture.Load("py_.jpg");
    skyboxM->cubeTexture.Load("pz_.jpg");
    skyboxM->cubeTexture.Load("nz_.jpg");
    skyboxM->cubeTexture.Init();
    skyBox = new SkyBox(skyboxM);
    //init skybox
    skyBox->InitVAO();
    
    //Add skybox to scene.
    skyBox->sceneNode.RotateX(180);
    SceneManager::GetInstance().AddSkyBox(skyBox);
    
    //Add house to scene 
    Mesh3D * house= MeshFactory::GetInstance()->GetMesh("house");
    //house->GetMaterial()->SetShader("test");
    house->sceneNode.SetScale(glm::vec3(0.01,0.01,0.01));
    house->sceneNode.SetPosition(glm::vec3(-70,2,0));
    SceneManager::GetInstance().AddToScene(house);
    house->SetRenderTech(CASTSHADOW);

    
    
    Mesh3D * eagle= MeshFactory::GetInstance()->GetMesh("eagle");
    //house->GetMaterial()->SetShader("test");
    eagle->sceneNode.SetScale(glm::vec3(1,1,1));
    eagle->sceneNode.SetPosition(glm::vec3(200*sin(0),25,200*cos(0)));
    eagle->sceneNode.RotateX(-90);
    SceneManager::GetInstance().AddToScene(eagle);
    SceneManager::GetInstance().AddToTickable(eagle);
    eagle->SetRenderTech(CASTSHADOW);//texture not matched
    
    terrain * gameterrain = new terrain();
    gameterrain->SetRenderTech(CASTSHADOW);
    //
    TerrainMaterial * terrainMat =   new TerrainMaterial();
    terrainMat->SetShader("terrain");
    terrainMat->SetTexture(MIDDLE, "grass.jpg");
    terrainMat->SetTexture(LOW, "shatter.jpg");
    terrainMat->SetTexture(HEIGH, "moss-texture.jpg");
    terrainMat->SetTexture(NORMALLOW, "shatterN.png");
    terrainMat->SetTexture(NORMALMIDDLE, "grassN.png");
    terrainMat->SetTexture(NORMALHEIGH, "moss-texture_NRM.png");
    
    gameterrain->AttachMaterial(terrainMat);
    gameterrain->LoadHightMap("heightmap1.jpg", 40);
    gameterrain->InitVAO();
    SceneManager::GetInstance().AddToScene(gameterrain);
    gameterrain->sceneNode.SetPosition(glm::vec3(-100.0,-5.0,-100.0));
    gameterrain->GenPlant();

    
    Water * water = new Water(80,30,30,1,1);
    water->InitVAO();
    water->sceneNode.SetPosition(glm::vec3(25,9,15));
    SceneManager::GetInstance().AddToScene(water);
    SceneManager::GetInstance().AddWater(water);
    SceneManager::GetInstance().AddToTickable(water);

    
    Mesh3D * tree= MeshFactory::GetInstance()->GetMesh("bamboo");
    tree->sceneNode.SetPosition(glm::vec3(-50,0,-30));
    //SceneManager::GetInstance().AddToScene(tree);
 
    
    Mesh3D * htree= MeshFactory::GetInstance()->GetMesh("hightree");
   
    htree->sceneNode.SetPosition(glm::vec3(-50,0,-50));
   // SceneManager::GetInstance().AddToScene(htree);
    _sound.LoadContent();
    _sound.Init();
    
 

}
Assignment::~Assignment()
{
     if (skyBox!=NULL);
    {
        delete skyBox;
        skyBox = NULL;
    }
    if (_camera=NULL)
    {
        delete _camera;
        _camera;
    }
}
void Assignment::Render()
{


    
}
void Assignment::Run()
{
    

  while (1)
  {
      _lasTime=SDL_GetTicks();

      _inputhandler.Tick(_FPS/1000);
      SceneManager::GetInstance().Tick(_FPS/1000);
      SceneManager::GetInstance().Render();
      _sound.Play();
      _currentTime=SDL_GetTicks();
    
      int _frameTime=_currentTime-_lasTime;
      
      if (_frameTime<_FPS/1000)
      {
          SDL_Delay((int)(_FPS/1000- _frameTime));
      }


  }
    
}