//
//  CubeTexture.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/24/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "CubeTexture.h"
CubeTexture::~CubeTexture()
{
    glDeleteTextures(1, &_texID);
    
    for (int i=0; i<_index; i++)
    {
        delete _texture[i];
        
    }
    
}
CubeTexture::CubeTexture()
{
     _texID=0;
     _texUnit=GL_TEXTURE0;
     _index=0;
     _unitIndex = 0;
}
void CubeTexture::Init()
{
    
   
    glEnable(GL_TEXTURE_CUBE_MAP);
    
    if (_hasImage)
    {
      glActiveTexture(_texUnit);

        glGenTextures(1, &_texID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);
        
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, _size, _size, 0, GL_RGB, GL_UNSIGNED_BYTE, _texture[0]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, _size, _size, 0, GL_RGB, GL_UNSIGNED_BYTE, _texture[1]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, _size, _size, 0, GL_RGB, GL_UNSIGNED_BYTE, _texture[2]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, _size, _size, 0, GL_RGB, GL_UNSIGNED_BYTE, _texture[3]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, _size, _size, 0, GL_RGB, GL_UNSIGNED_BYTE, _texture[4]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, _size, _size, 0, GL_RGB, GL_UNSIGNED_BYTE, _texture[5]);
    }
    else
    {
        
        glActiveTexture(_texUnit);
        glGenTextures(1, &_texID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);
        //set texture parameters
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        for (int i = 0; i <6 ; i++)
        {
         glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, _size, _size, 0, GL_RGBA, GL_FLOAT, NULL);
        }
        
    }
        
    //glClearColor( 1.0, 1.0, 1.0, 0.0 );
	glClearDepth( 1.0 );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc(GL_LEQUAL);
    
   // std::cout<<"TextureInit";
}
bool CubeTexture::Load(std::string fileName)
{
    std::cout<<fileName.c_str();
    int width = 0,height=0;
    _texture[_index] =SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    _size=width;
    if (!_texture[_index])
    {
        return false;
    }
  //  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
  //               GL_UNSIGNED_BYTE, &_texture[_index]);
    _hasImage = true;
    _index++;
    return true;
}
void CubeTexture::Bind()
{
    glActiveTexture(_texUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);
}
void CubeTexture::AttachByFrameBuffer( int size)
{
    

    _texUnit = GL_TEXTURE8;
    _hasImage = false ;
    _unitIndex = 8;
    
    _size = size;

}
int  CubeTexture::GetUnitIndex()
{
    return _unitIndex;
}
int CubeTexture::GetID()
{
    return _texID;
}


