//
//  SceneManager.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "SceneManager.h"
SceneManager SceneManager::_instance;
SceneManager::SceneManager()
{
   
    _viewMatrix = glm::mat4(1.0);
    _proMatrix  = glm::mat4(1.0);
    _modelMatrix= glm::mat4(1.0);
    
    _dLight=new DirectionLight();
    this->AddToTickable(_dLight);

};
void SceneManager::AddToScene(IDrawable * node)
{
    _renderList.push_back(node);
    
}
void SceneManager::RemoveFromScene(IDrawable * node)
{
    _renderList.remove(node);
}

void SceneManager::PostPass()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDisable(GL_BLEND);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.5f,10.0f);
    
    _shadowBuffer->Bind();
    _shadowBuffer->Clear();
    _shadowBuffer->ResetViewPort();

    
    ShaderLibrary::GetShader("shadow")->Bind();
    
    for (it=_renderList.begin(); it!=_renderList.end(); ++it)
    {
        
        _matStack.push(_modelMatrix);
        
        IDrawable * currentObject = (*it);
        if (currentObject->CheckRenderTech(CASTSHADOW)==false)
        {
            continue;
        }
        
        
        _modelMatrix*=currentObject->sceneNode.GetTransformMatrix();
        
        
        if (currentObject->CheckRenderTech(CASTALPHASHADOW)==true)
        {
            
            ShaderLibrary::GetShader("shadow")->PushUniform("hasAlpha", true);
            ShaderLibrary::GetShader("shadow")->PushUniform("mvp", _dLight ->GetLightPV()*_modelMatrix);
            ShaderLibrary::GetShader("shadow")->PushUniform("texAlpha", 1);
            
        }
        else
        {
            ShaderLibrary::GetShader("shadow")->PushUniform("hasAlpha", false);
            ShaderLibrary::GetShader("shadow")->PushUniform("mvp", _dLight ->GetLightPV()*_modelMatrix);
        }
        
        currentObject->Draw();

        _modelMatrix=_matStack.top();
        _matStack.pop();
        
        
    }
    
     _shadowBuffer ->UnBind();
     glDisable(GL_POLYGON_OFFSET_FILL);
     glDisable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
     glViewport(0, 0, 500, 500);
    
}


void SceneManager::ColorPass()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    
    for (it=_renderList.begin(); it!=_renderList.end(); ++it)
    {
        
        _matStack.push(_modelMatrix);
        
        
        IDrawable * currentObject = (*it);
        
        //Get the model matrix from scenenode
        currentObject->GetMaterial()->Bind();
        
        _modelMatrix*=currentObject->sceneNode.GetTransformMatrix();
        
        this->UpdateWorldMatrix(currentObject->GetMaterial());
        
        

       
        if (currentObject->CheckRenderTech(HASAABB))
        {
            
        }
        
        currentObject->Draw();
        
        
        //restore the world model matrix
        _modelMatrix=_matStack.top();
        _matStack.pop();
        
        
    }
    
    SDL_GL_SwapWindow(_renderContext->GetRenderWindow());
    
    //       this->UpdateWorldMatrix();
    //       drawable->GetMaterial()->Bind();
    //       drawable->Draw();
}

void SceneManager::Render()
{
     PostPass();
     EnviPass();
     ColorPass();
    
}
void SceneManager::Init()
{
    
    
    _shadowBuffer = new ShadowBuffer ();
    _shadowBuffer ->Init();
    
    _reflectBuffer = new FrameBufferObject();
    _reflectBuffer->Init();
    
    
    _envBuffer =  new FrameBufferObject3D();
    _envBuffer->SetSize(512);
    _envBuffer -> Init();
    
    
    
}

void SceneManager::SetCamera(ICamera *camera)
{
    _camera=camera;
}
void SceneManager::SetOpenGLContext(OpenGLContext *context)
{
    _renderContext=context;
}

 SceneManager &SceneManager::GetInstance()
{
    return _instance;
}
const glm::mat4 & SceneManager::GetWorldModelMatrix()
{
    return _modelMatrix;
}
 ICamera *SceneManager::GetCamera()
{
    return _camera;
}
const glm::mat4  SceneManager::GetWorldViewMatrix()
{
    
    return _viewMatrix;
    
    
}
const glm::mat4  SceneManager::GetWorldProjMatrix()
{
    return  _proMatrix;
}
void SceneManager::AddToTickable(ITickable *tick)
{
    _tickList.push_back(tick);
}
void SceneManager::RemoveFromTickable(ITickable *tick)
{
    _tickList.remove(tick);
}
void SceneManager::Tick(float dt)
{
    for (_tick=_tickList.begin(); _tick!=_tickList.end(); ++_tick)
    {
        (*_tick)->Tick(dt);
    }
}
void  SceneManager::UpdateWorldMatrix(IMaterial * material)
{
    _viewMatrix =_camera->GetViewMatrix();
    
    
    
    _proMatrix = _camera->GetProjectionMatrix();
    _mv = _viewMatrix*_modelMatrix;
    
   
    
    _nv = glm::transpose(glm::inverse(glm::mat3(_mv)));
    _mvp=_proMatrix*_mv;
    
   // sceneMat["view"] = ge
    
   // _viewMatrix =glm::inverse(glm::inverse(_viewMatrix)) ;
    _viewMatrix =_camera->GetCameraWorld();
    material->GetShader()->PushUniform("model",_modelMatrix);
    material->GetShader()->PushUniform("view", _viewMatrix);
    material->GetShader()->PushUniform("projection", _proMatrix);
    material->GetShader()->PushUniform("nv", _nv);
    material->GetShader()->PushUniform("mv", _mv);
    material->GetShader()->PushUniform("mvp", _mvp);

    _mvp =_dLight->GetLightPV();
}
const glm::mat3  &SceneManager::GetNV()
{
    return _nv;
}
const glm::mat4  &SceneManager::GetMVPMatrix()
{
    
   return  _mvp;
}
const glm::mat4  &SceneManager::GetMPMatrix()
{
    return _vp;
}
DirectionLight * SceneManager::Getlight()
{
    return _dLight;
}
void SceneManager::AddSkyBox(SkyBox * skyBox)
{
    _skyBox=skyBox;
    _skyBox->_camera = this->_camera;
    this->AddToScene(_skyBox);
}
const glm::mat4  &SceneManager::GetMV()
{
   return _mv;
}
void SceneManager::AddWater(Water * water)
{
    _water = water;
    _water->SetCamera(_camera);
}


void SceneManager::ReflectPass()
{
    _reflectBuffer->Bind();
    _reflectBuffer->ResetViewPort();
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // glEnable(GL_CULL_FACE);
   // glCullFace(GL_FRONT);
    
    for (it=_renderList.begin(); it!=_renderList.end(); ++it)
    {
        
        _matStack.push(_modelMatrix);
        
       
        
        IDrawable * currentObject = (*it);
        

        if(currentObject->CheckRenderTech(REFLECTION))
        {
            continue;
        }
       _camera->SetViewMatrix(_water->GetReflectMatrix());
    
        
        //Get the model matrix from scenenode
        currentObject->GetMaterial()->Bind();
        
       _modelMatrix*=currentObject->sceneNode.GetTransformMatrix();
        

        this->UpdateWorldMatrix(currentObject->GetMaterial());


        
        currentObject->Draw();
        
        
        //restore the world model matrix
        _modelMatrix=_matStack.top();
        _matStack.pop();
        
        
    }
   //  glCullFace(GL_BACK);
   // glDisable(GL_CULL_FACE);
   
  // SDL_GL_SwapWindow(_renderContext->GetRenderWindow());
    glViewport(0, 0, 500, 500); 
   _reflectBuffer->UnBind();
}
void SceneManager::EnviPass()
{
    _envBuffer->ResetViewPort();
    
    _envBuffer->Bind();
    _envBuffer->Clear();
    _envBuffer->SetCurrentFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
    

    glm::mat4 MV1 = glm::lookAt(glm::vec3(0),glm::vec3(1,0,0), glm::vec3(0,-1,0));
    glm::mat4 cameraTransation1 = glm::translate(MV1, _camera->GetPosition()) ;
    // MV1*=_camera->GetViewMatrix();
    _camera->SetViewMatrix(cameraTransation1);
    //RenderUnReflectObject();
    _envBuffer->UnBind();
        
    
     _envBuffer->Bind();
     _envBuffer->Clear();
    _envBuffer->SetCurrentFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
     glm::mat4 MV2 = glm::lookAt(glm::vec3(0),glm::vec3(-1,0,0), glm::vec3(0,-1,0));
     glm::mat4 cameraTransation2 = glm::translate(MV2, _camera->GetPosition()) ;

    _camera->SetViewMatrix(cameraTransation2);
    //RenderUnReflectObject();
    _envBuffer->UnBind();

    
    _envBuffer->Bind();
    _envBuffer->Clear();
    _envBuffer->SetCurrentFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
     MV1*=_camera->GetViewMatrix();
     glm::mat4 MV3 = glm::lookAt(glm::vec3(0),glm::vec3(0,1,0), glm::vec3(1,0,0));
     _camera->SetViewMatrix(MV3);
    // RenderUnReflectObject();
    // _envBuffer->UnBind();
    
    
    
    _envBuffer->Bind();
    _envBuffer->Clear();
    _envBuffer->SetCurrentFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
    glm::mat4 MV4 = glm::lookAt(glm::vec3(0),glm::vec3(0,-1,0), glm::vec3(1,0,0));
    
    MV4*=_camera->GetViewMatrix();
    _camera->SetViewMatrix(MV4);
   // RenderUnReflectObject();
    // _envBuffer->UnBind();
    
    
    _envBuffer->Bind();
    _envBuffer->Clear();
    _envBuffer->SetCurrentFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
     MV1*=_camera->GetViewMatrix();
    glm::mat4 MV5 = glm::lookAt(glm::vec3(0),glm::vec3(0,0,1), glm::vec3(0,-1,0));
    _camera->SetViewMatrix(MV5);
    RenderUnReflectObject();
   //  _envBuffer->UnBind();
    
    
    
    _envBuffer->Bind();
    _envBuffer->Clear();
    _envBuffer->SetCurrentFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
     MV1*=_camera->GetViewMatrix();
    glm::mat4 MV6 = glm::lookAt(glm::vec3(0),glm::vec3(0,0,-1), glm::vec3(0,-1,0));
    _camera->SetViewMatrix(MV6);
   // RenderUnReflectObject();
    
    _envBuffer->UnBind();
    glViewport(0, 0, 500, 500);
}
void SceneManager::RenderUnReflectObject()
{
    
    for (it=_renderList.begin(); it!=_renderList.end(); ++it)
    {
        
        _matStack.push(_modelMatrix);
        
        
        
        IDrawable * currentObject = (*it);
        
        
        if(currentObject->CheckRenderTech(REFLECTION))
        {
            continue;
        }
        
 
        
        //Get the model matrix from scenenode
        currentObject->GetMaterial()->Bind();
        
        _modelMatrix*=currentObject->sceneNode.GetTransformMatrix();
        
        
        this->UpdateWorldMatrix(currentObject->GetMaterial());
        
        
        
        currentObject->Draw();
        
        _modelMatrix=_matStack.top();
        _matStack.pop();
        
    }
}
void SceneManager::ClearScene()
{
    if (_dLight != NULL )
    {
        delete _dLight;
    }
    if (_envBuffer!=NULL)
    {
        delete _envBuffer;
    }
    if (_shadowBuffer!=NULL)
    {
        delete _dLight;
    }
}
SceneManager::~SceneManager()
{
    ClearScene();
    _renderList.clear();
    delete  _renderContext;

}