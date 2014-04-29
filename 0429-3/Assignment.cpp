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
    
    SceneManager::GetInstance().Init();
    
    
    ShaderLibrary::Init();
    _camera  =new FPSCamera();
    SceneManager::GetInstance().SetCamera(_camera);
    SceneManager::GetInstance().AddToTickable(_camera);
    
    
    SkyBoxMaterial* skyboxM=new SkyBoxMaterial();
    skyboxM->cubeTexture.Load("px_.jpg");
    skyboxM->cubeTexture.Load("nx_.jpg");
    skyboxM->cubeTexture.Load("ny_.jpg");
    skyboxM->cubeTexture.Load("py_.jpg");
    skyboxM->cubeTexture.Load("pz_.jpg");
    skyboxM->cubeTexture.Load("nz_.jpg");
    //
    skyboxM->cubeTexture.Init();
    
    skyBox = new SkyBox(skyboxM);
    //init skybox
    skyBox->InitVAO();
    //add to scene.
    skyBox->sceneNode.RotateX(180);
    SceneManager::GetInstance().AddSkyBox(skyBox);
    
    
    
//
    
    
//    IDrawable *plane = new Plane(100,50,50,10,10);
//    plane ->SetRenderTech(CASTSHADOW);
//
//    Mesh3DMaterial * PlaneMat =   new Mesh3DMaterial ();
//    PlaneMat ->SetShader("test");
//    PlaneMat ->SetTexture(DIFFUSE ,"Dbricks.jpg");
//    PlaneMat ->SetTexture(NORMAL ,"Dbricks.jpg");
//    plane->AttachMaterial(PlaneMat);
//    plane->InitVAO();
//    plane->sceneNode.SetPosition(glm::vec3(0,0,0));
//    SceneManager::GetInstance().AddToScene(plane);

    
    
    
    Mesh3D * house= MeshFactory::GetInstance()->GetMesh("house");
    //house->GetMaterial()->SetShader("test");
    house->sceneNode.SetScale(glm::vec3(0.01,0.01,0.01));
    house->sceneNode.SetPosition(glm::vec3(-70,2,0));
    SceneManager::GetInstance().AddToScene(house);
    house->SetRenderTech(CASTSHADOW);
    
//    Mesh3D * house2= MeshFactory::GetInstance()->GetMesh("house");
//    //house->GetMaterial()->SetShader("test");
//    house2->sceneNode.SetScale(glm::vec3(0.01,0.01,0.01));
//    house2->sceneNode.SetPosition(glm::vec3(-85,2,0));
//    SceneManager::GetInstance().AddToScene(house2);
//    house2->SetRenderTech(CASTSHADOW);
    
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
    
    
//    Mesh3D * house1= MeshFactory::GetInstance()->GetMesh("house");
//    house1->GetMaterial()->SetShader("test");
//    house1->sceneNode.SetScale(glm::vec3(0.01,0.01,0.01));
//    house1->sceneNode.SetPosition(glm::vec3(0,40.0,0));
//    house1->sceneNode.RotateY (45);
//    SceneManager::GetInstance().AddToScene(house1);
//    house1->SetRenderTech(CASTSHADOW);
    
    Water * water = new Water(80,30,30,1,1);
    water->InitVAO();
    water->sceneNode.SetPosition(glm::vec3(25,9,15));
    SceneManager::GetInstance().AddToScene(water);
    SceneManager::GetInstance().AddWater(water);
    SceneManager::GetInstance().AddToTickable(water);
    
    
    //SceneManager::GetInstance().AddToTickable(house);
//    
////
    

    
    

    
    

    
    //gameterrain->sceneNode.SetPosition(glm::vec3(0,2,0));
    //gameterrain->sceneNode.RotateZ(90);
    
    
    
//    Texture2D * planeColor =Texture2D::CreateNextUnit();
//    planeColor->Load("planeDiffuse.png");
//    Texture2D * planeNormal = Texture2D::CreateNextUnit();
//    planeNormal->Load("planeNormal.bmp");
//    pm->SetNorml(planeNormal);
//    pm->SetDiff(planeColor);
//    pm->Init();
//    plane->AttachMaterial(pm);
//
    
    
//
//
//    
//    IDrawable *plane1 = new Plane(100,10,10,10,10);
//    plane1 ->SetRenderTech(CASTSHADOW);
//    plane1->InitVAO();
//    Mesh3DMaterial * pm2 =   new Mesh3DMaterial ();
//    pm2 ->SetShader("test");
////    Texture2D * planeColor1 =Texture2D::CreateNextUnit();
////    planeColor1->Load("planeDiffuse.png");
////    Texture2D * planeNormal1 = Texture2D::CreateNextUnit();
////    planeNormal1->Load("planeNormal.bmp");
////    pm2->SetNorml(planeNormal1);
////    pm2->SetDiff(planeColor1);
//    pm2->Init();
//    plane1->AttachMaterial(pm2);
//    plane1->sceneNode.RotateZ(-90);
//    plane1->sceneNode.SetPosition(glm::vec3(-5,30,0));
//    //SceneManager::GetInstance().AddToScene(plane1);
//    
//    
//    Cube * cube  = new Cube(50);
//    Mesh3DMaterial * cubeMat =   new Mesh3DMaterial ();
//    cubeMat->SetShader("test");
////    cubeMat->SetNorml("Resource/house_normal.png");
////    cubeMat->SetDiff("planeNormal.bmp");
//    
//    cube->InitVAO();
//    cube->AttachMaterial(cubeMat);
//   // cube->sceneNode.SetPosition(glm::vec3(10,0,0));
    
    
    
    // plane->sceneNode.RotateX(90);
   // SceneManager::GetInstance().AddToScene(cube);
    //SceneManager::GetInstance().AddToTickable(cube);
//
//    
//    Cube * cube2  = new Cube(50);
//    cube2->InitVAO();
//    WaterMaterial  * pm3 =   new WaterMaterial("a");
//    pm3->SetShader("normal");
//    cube2->SetRenderTech(CASTSHADOW);
//    pm3->Init();
//    cube2->AttachMaterial(pm3);
//    cube2->sceneNode.SetPosition(glm::vec3(0,50,0));
//    SceneManager::GetInstance().AddToScene(cube2);
   // SceneManager::GetInstance().AddToTickable(cube2);
    
    
    
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