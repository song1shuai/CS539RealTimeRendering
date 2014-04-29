//
//  Texture2D.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/23/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Texture2D.h"
int Texture2D::SystemUnitIndex=0;
std::map<int, GLenum> Texture2D::unitID=
{
    std::make_pair(0,GL_TEXTURE0),
    std::make_pair(1,GL_TEXTURE1),
    std::make_pair(2,GL_TEXTURE2),
    std::make_pair(3,GL_TEXTURE3),
    std::make_pair(4,GL_TEXTURE4),
    std::make_pair(5,GL_TEXTURE5),
    std::make_pair(6,GL_TEXTURE6),
    std::make_pair(7,GL_TEXTURE7),
    std::make_pair(8,GL_TEXTURE8),
    std::make_pair(9,GL_TEXTURE9),
    std::make_pair(10,GL_TEXTURE10),
};
Texture2D::Texture2D()
{
    _height = 0;
    _width = 0;
    _minfiler = GL_LINEAR;
    _magfiler = GL_LINEAR;
    _texID=0;
    _type=GL_TEXTURE_2D;
    _unitIndex=SystemUnitIndex;
    _texUnit=this->unitID[_unitIndex];
    _image=NULL;
    _format =GL_RGBA;
    _hasImage = false;
}
Texture2D::Texture2D(int index)
{
    _height = 0;
    _width = 0;
    _minfiler = GL_LINEAR;
    _magfiler = GL_LINEAR;
    _texID=0;
    _unitIndex=index;
    _texUnit=this->unitID[index];
    _image=NULL;
    _hasImage = false;
}
bool Texture2D::Load(std::string fileName)
{
    

   
    _image =SOIL_load_image(fileName.c_str(), &_width, &_height, 0, SOIL_LOAD_RGB);
    
    if (_image==NULL)
    {
    std::cout<<"Error loading texture "<<fileName.c_str()<<std::endl;
        return false;
       
    }
    std::cout<<"Loaded texture "<<fileName.c_str()<<std::endl;

    _hasImage = true ;
    
    return  true;
}
void Texture2D::Init()
{
    
    glActiveTexture(_texUnit);
    glGenTextures(1, &_texID);
    glBindTexture(GL_TEXTURE_2D, _texID);
    
    if (_hasImage)
    {
      
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, _image);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minfiler);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magfiler);
        
        
        SOIL_free_image_data(_image);
        _image=NULL;
        
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        if(_format == GL_DEPTH_COMPONENT)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, boardColor1);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, boardColor2);
        }
    }
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minfiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magfiler);

    
}
Texture2D::~Texture2D()
{
    glDeleteTextures(1, &_texID);
}
void Texture2D::Bind()
{
    glActiveTexture(_texUnit);
    glBindTexture(GL_TEXTURE_2D, _texID);
}

void Texture2D::SetFilter(GLenum min,GLenum mag)
{
    _minfiler=min;
    _magfiler=mag;
    
}
  Texture2D *Texture2D::CreateNextUnit()
{
    int index = Texture2D::GetNextUnitIndex();
    Texture2D * texture = new Texture2D(index);
    
    return texture;
}

int Texture2D::GetNextUnitIndex()
{
    int index =SystemUnitIndex;
    SystemUnitIndex++;
    if (SystemUnitIndex>10)
    {
        SystemUnitIndex=0;
    }
    
    return index;
}
void Texture2D::ReSetSUnitIndex()
{
    SystemUnitIndex=0;
}
int Texture2D::GetUnitIndex()
{
    return _unitIndex;
}
void Texture2D::AttachByFrameBuffer(int texUnit,int width , int height ,int format ,int sytermFormat)
{
 
    _width  = width;
    _height = height;
    
    _format = format;
    
    _hasImage = false ;
    _sytermFormat = sytermFormat;
    _unitIndex = texUnit;
    _texUnit=this->unitID[_unitIndex];
}