//
//  Water.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/18/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Water.h"
Water::Water(float size,
             int xdivs,
             int zdivs,
             float smax,
             float tmax
             ):_waterSurface(size,
                            xdivs,
                            zdivs,
                            smax,
                            tmax
                            )
{

    _material = new WaterMaterial("waterN.png");
    this->SetRenderTech(REFLECTION);
    _waterHeight = 0.0;
    _mirrorMat = glm::mat4(1.0);
    glm::value_ptr(_mirrorMat)[5]=-1;
    _tickTime = 0;
    
    _boundingBox =  new BoundingBox();
    _boundingBox->GreatFromVertex(_waterSurface._vertices);
    GenWave();
    
}
void Water::Draw()
{
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    this->GetMaterial()->GetShader()->PushUniform("dt", _tickTime);

    this->GetMaterial()->GetShader()->PushUniform2DArray("directions", 4, glm::value_ptr(_directions[0]));
    this->GetMaterial()->GetShader()->PushUniform4DArray("wavaParam", 4, (float*)_waveParam);
    
    _waterSurface.Draw();
    _boundingBox->Draw();
}

void Water::InitVAO()
{
    _boundingBox->InitVAO();
    _material->Init();
    _waterSurface.InitVAO();
}
void Water::Tick(float dt)
{
    
    _tickTime+=0.1;
   
}
void Water::SetCamera(ICamera * camera)
{
    _camera = camera;
}
glm::mat4 Water::GetReflectMatrix()
{
    glm::vec3 pos = _camera->GetPosition();
    glm::vec3 target = pos-_camera->GetForwardVector();
    
    
    pos.z = 2.0 * _waterHeight - pos.z;
    target.z = 2.0 * _waterHeight + target.z;
        
    glm::vec3 waterForward = target - pos;
    glm::vec3 waterSide = _camera->GetRight();
    glm::vec3 waterUp = glm::cross(waterSide, waterForward);
        
    _waterView =  glm::lookAt(pos, target, waterUp);
    

     return _mirrorMat*_waterView;
}
void Water::RandomDirection()
{
    for( int i=0 ; i<4 ; i++ )
    {
		float angle = Random1D(-M_PI/3.0f, M_PI/3.0f);
		_directions[i]=glm::vec2(cos(angle),sin(angle));
	}
}
void Water::GenWave()
{
    
 
    
    //same fix water param  could be random generated
    
    int overallSteepness = 0.2;
    
	_waveParam[0].speed = 0.05;
	_waveParam[0].amplitude = 0.02f;
	_waveParam[0].wavelength = 0.3f;
	_waveParam[0].steepness = overallSteepness / (_waveParam[0].wavelength * _waveParam[0].amplitude * 4);
    
    
	_directions[0].x = +1.0f;
	_directions[0].y = +1.5f;
    
	// Wave Two
	_waveParam[1].speed = 0.1f;
	_waveParam[1].amplitude = 0.01f;
	_waveParam[1].wavelength = 0.4f;
	_waveParam[1].steepness = overallSteepness / (_waveParam[1].wavelength * _waveParam[1].amplitude * 4);
    
	_directions[1].x = +0.8f;
	_directions[1].y = +0.2f;
    
	// Wave Thre
	_waveParam[2].speed = 0.04f;
	_waveParam[2].amplitude = 0.35f;
	_waveParam[2].wavelength = 0.1f;
	_waveParam[2].steepness = overallSteepness / (_waveParam[1].wavelength * _waveParam[1].amplitude * 4);
	_directions[2].x = -0.2f;
	_directions[2].y = -0.1f;
    
	// Wave Four
	_waveParam[3].speed = 0.05f;
	_waveParam[3].amplitude = 0.007f;
	_waveParam[3].wavelength = 0.2f;
	_waveParam[3].steepness = overallSteepness / (_waveParam[1].wavelength * _waveParam[1].amplitude * 4);
	_directions[3].x = -0.4f;
	_directions[3].y = -0.3f;
}
Water::~Water()
{
    
    delete _boundingBox;
}
