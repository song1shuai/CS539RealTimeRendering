//
//  SceneManager.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__SceneManager__
#define __CS539_SHUAI_SONG__SceneManager__

#include <iostream>
#include <list>
#include "ISceneNode.h"
#include "OpenGLContext.h"
#include "IDrawable.h"
#include <stack>
#include "ITickable.h"
#include "matrix_transform.hpp"
#include "DirectionLight.h"
#include "SkyBox.h"
#include "ShadowBuffer.h"
#include "ShaderLibrary.h"
#include "ITexture.h"
#include "Water.h"
#include "FrameBufferObject.h"
#include "FrameBufferObject3D.h"
#include <map>

#define  SHADOWMAP_TEX_ID 10

typedef std::list<IDrawable*> SENCENODELIST;
typedef std::list<ITickable*> TICKLIST;

class SkyBox;
class Water;
class SceneManager
{
    
private:
    
    /*
     Render and tick list
     */
    
    SENCENODELIST _renderList;
    SENCENODELIST::iterator it;
    
    TICKLIST _tickList;
    TICKLIST::iterator _tick;
    OpenGLContext* _renderContext;
    
    
private:
    /*
     The matrix
     
     */
  
    std::stack<glm::mat4> _matStack;
    
    glm::mat4 _viewMatrix;
    glm::mat4 _proMatrix;
    glm::mat4 _modelMatrix;
    /*
     
     
     */
    glm::mat4 _mvp;
    glm::mat4 _vp;
    glm::mat3 _nv;
    glm::mat4 _mv;
    
   //std::map<string, glm::mat4> sceneMat;
private:
    
    std::map<string, glm::mat4> sceneMat;
    
    ICamera* _camera;
    DirectionLight * _dLight;
    
    float _FPS;
    //IDrawable * _curDrawable;
    static SceneManager _instance;
    SceneManager();
    ~SceneManager();
    SkyBox * _skyBox;
    Water * _water;
   
    bool _isShadowPass;
   // ITexture * _jitterTexture;
    ShadowBuffer* _shadowBuffer;
    FrameBufferObject * _reflectBuffer;
    FrameBufferObject3D * _envBuffer;
    
    void ReflectPass();
    void EnviPass();
    void RenderUnReflectObject();
    
public:
    
    
    
    ITexture * _jitterTexture;
    glm::vec3 _jitterVector;
    void ColorPass();
    void PostPass();
    
    void Init();
    void AddToScene(IDrawable * node);
    
    void AddToTickable(ITickable *tick);
    void RemoveFromTickable(ITickable *tick);
    
    void RemoveFromScene(IDrawable * node);
    
    //void ShadowPass(IDrawable * objectM);
    void Render();
    void Tick(float dt);
    void SetCamera( ICamera *camera);
    void SetOpenGLContext( OpenGLContext *context);
    void SetFPS();
    static SceneManager &GetInstance();
    
    const glm::mat4  &GetMV();
    const glm::mat3  &GetNV();
    const glm::mat4  &GetMVPMatrix();
    const glm::mat4  &GetMPMatrix();
    
    const glm::mat4  &GetWorldModelMatrix();
    const glm::mat4 GetWorldViewMatrix();
    const glm::mat4  GetWorldProjMatrix();
    void  AddSkyBox(SkyBox * _skyBox);
    void  AddWater(Water * Water);
    void  UpdateWorldMatrix(IMaterial * material);
    
   // bool IsShadowPass();
    DirectionLight * Getlight();
    ICamera *GetCamera();
    void ClearScene();
};

#endif /* defined(__CS539_SHUAI_SONG__SceneManager__) */
