//
//  ShaderLibrary.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "ShaderLibrary.h"

map<string, Shader*> ShaderLibrary::shaders;
map<string, Shader*>::iterator ShaderLibrary::iter;

Shader* ShaderLibrary::GetShader(string ShaderName)
{
    
    iter=shaders.find(ShaderName);
    
    if (iter==shaders.end())
    {
        cout<<"can not find shader"<<ShaderName;
        
        assert(false);
    }
    
    return shaders[ShaderName];
    
}
void ShaderLibrary::AddShader(Shader* shader)
{
    shaders[shader->GetName()]=shader;
}
void ShaderLibrary::ClearUp()
{
    shaders.clear();
}
void ShaderLibrary::Init()
{
    
    Shader* _skyBoxShader=new Shader();
    /*
     Note: USE GL_??_SHADER
     */
    
    //add sky box shader
    _skyBoxShader->LoadFromFile(GL_VERTEX_SHADER, "vSkyBox.glsl");
    _skyBoxShader->LoadFromFile(GL_FRAGMENT_SHADER, "fSkyBox.glsl");
    _skyBoxShader->SetName("skyBox");
    
    _skyBoxShader->CreateShaderProgram();
    
    _skyBoxShader->AddUniform("cubeSampler");
    _skyBoxShader->AddUniform("model");
    _skyBoxShader->AddUniform("view");
    _skyBoxShader->AddUniform("projection");
    _skyBoxShader->AddUniform("mvp");
    
    AddShader(_skyBoxShader);
    
    
    //add 3dmesh shader
    Shader* Mesh3DShader=new Shader();
    Mesh3DShader->LoadFromFile(GL_VERTEX_SHADER, "vMesh.glsl");
    Mesh3DShader->LoadFromFile(GL_FRAGMENT_SHADER, "fMesh.glsl");
    Mesh3DShader->SetName("Mesh3D");
    Mesh3DShader->CreateShaderProgram();
    
    Mesh3DShader->AddUniform("mvp");
    Mesh3DShader->AddUniform("nv");
    Mesh3DShader->AddUniform("mv");
    Mesh3DShader->AddUniform("texNormal");
    Mesh3DShader->AddUniform("texSpecular");
    Mesh3DShader->AddUniform("texDiffuse");
    Mesh3DShader->AddUniform("model");
    Mesh3DShader->AddUniform("view");
    Mesh3DShader->AddUniform("lightPos");
    Mesh3DShader->AddUniform("lightIntensity");
    Mesh3DShader->AddUniform("projection");
    Mesh3DShader->AddUniform("ShadowMap");
    Mesh3DShader->AddUniform("hasAlpha");
    Mesh3DShader->AddUniform("hasDecal");
    AddShader(Mesh3DShader);
    
    // The test shader
    
    Shader* test=new Shader();
    test->LoadFromFile(GL_VERTEX_SHADER, "vlighttest.glsl");
    test->LoadFromFile(GL_FRAGMENT_SHADER, "flighttest.glsl");
    test->SetName("test");
    test->CreateShaderProgram();
    test->AddUniform("mv");
    test->AddUniform("nv");
    test->AddUniform("model");
    test->AddUniform("view");
    test->AddUniform("projection");
    test->AddUniform("lightPos");
    test->AddUniform("lightIntensity");
    test->AddUniform("mvp");
    test->AddUniform("lightSPV");
    test->AddUniform("ShadowMap");
    test->AddUniform("texNormal");
    test->AddUniform("texSpecular");
    test->AddUniform("texDiffuse");
    test->AddUniform("hasDecal");
    
    AddShader(test);
    
    
    // This shader use for cast shadow
    
    Shader* shadow=new Shader();
    shadow->LoadFromFile(GL_VERTEX_SHADER, "vShadow.glsl");
    shadow->LoadFromFile(GL_FRAGMENT_SHADER, "fShadow.glsl");
    shadow->SetName("shadow");
    shadow->CreateShaderProgram();
    shadow->AddUniform("mvp");
    
    AddShader(shadow);
    
    // This shader use for cast shadow witch mesh has alpha texture
    
    Shader* shadowA=new Shader();
    shadowA->LoadFromFile(GL_VERTEX_SHADER, "vShadowAlpha.glsl");
    shadowA->LoadFromFile(GL_FRAGMENT_SHADER, "fShadowAlpha.glsl");
    shadowA->SetName("shadowAlpha");
    shadowA->CreateShaderProgram();
    shadowA->AddUniform("mvp");
    shadowA->AddUniform("texAlpha");
    shadowA->AddUniform("hasAlpha");
    AddShader(shadowA);
    
    
    //This shader use for terrain generation
    
    Shader* terrain=new Shader();
    terrain->LoadFromFile(GL_VERTEX_SHADER, "vTerrain.glsl");
    terrain->LoadFromFile(GL_FRAGMENT_SHADER, "fTerrain.glsl");
    terrain->SetName("terrain");
    terrain->CreateShaderProgram();
    
    terrain->AddUniform("mv");
    terrain->AddUniform("nv");
    terrain->AddUniform("model");
    terrain->AddUniform("view");
    terrain->AddUniform("projection");
    terrain->AddUniform("lightPos");
    terrain->AddUniform("lightIntensity");
    terrain->AddUniform("mvp");
    terrain->AddUniform("lightSPV");
    terrain->AddUniform("ShadowMap");
    terrain->AddUniform("texLow");
    terrain->AddUniform("texMiddle");
    terrain->AddUniform("texHeigh");
    terrain->AddUniform("texDecal");
    terrain->AddUniform("texNormal");
    terrain->AddUniform("texNormalHeigh");
    terrain->AddUniform("texNormalMiddle");
    terrain->AddUniform("texNormalLow");
    
    AddShader(terrain);
    
    
    //This shader use for generation water
    
    Shader* water=new Shader();
    water->LoadFromFile(GL_VERTEX_SHADER, "vWater.glsl");
    water->LoadFromFile(GL_FRAGMENT_SHADER, "fWater.glsl");
    water->SetName("water");
    water->CreateShaderProgram();
    
    water->AddUniform("mv");
    water->AddUniform("nv");
    water->AddUniform("dt");
    water->AddUniform("mvp");
    water->AddUniform("lightPos");
    water->AddUniform("lightIntensity");
    water->AddUniform("waterSampler");
    water->AddUniform("directions");
    water->AddUniform("enviSampler");
    water->AddUniform("cubeSampler");
    water->AddUniform("reflectSampler");
    water->AddUniform("cameraPos");
    water->AddUniform("wavaParam");
    
    AddShader(water);
    
    
    // This shader use for generate plant
    Shader* plant=new Shader();
    plant->LoadFromFile(GL_VERTEX_SHADER, "vPlant.glsl");
    plant->LoadFromFile(GL_FRAGMENT_SHADER, "fPlant.glsl");
    plant->SetName("plant");
    plant->CreateShaderProgram();
    
    plant->AddUniform("mvp");
    plant->AddUniform("nv");
    plant->AddUniform("mv");
    plant->AddUniform("texNormal");
    plant->AddUniform("texAlpha");
    plant->AddUniform("texDiffuse");
    plant->AddUniform("model");
    plant->AddUniform("view");
    plant->AddUniform("lightPos");
    plant->AddUniform("lightIntensity");
    plant->AddUniform("projection");
    plant->AddUniform("ShadowMap");
    plant->AddUniform("hasAlpha");
    AddShader(plant);
    
}
ShaderLibrary:: ~ShaderLibrary()
{
    
    shaders.clear();
}