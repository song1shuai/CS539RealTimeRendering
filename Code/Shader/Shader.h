//
//  Shader.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__Shader__
#define __CS539_SHUAI_SONG__Shader__

#include <iostream>
#include <OpenGL/gl3.h>
#include <string>
#include <map>
#include <fstream>
#include "glm.hpp"
#include "Texture2D.h"
#include "CubeTexture.h"
#include "ext.hpp"

using namespace std;
enum ShaderType {
                 VERTEX_SHADER,
                 FRAGMENT_SHADER,
                 GEOMETRY_SHADER
                };
class Shader
{
    
private:
    
    std::string _name;
    GLuint      _program;
    int         _totalShaders;
	GLuint      _shaders[3];                                //0 ,vertexshader, 1,fragmentshader, 2,geometryshader
    
    std::map<std::string,GLuint> _attributes;               // The arrtibutes map
    std::map<std::string,GLuint> _uniformLocations;         // The uniform locations
    
public:
    
    Shader();
    ~Shader();
    bool CreateShaderProgram();
    void Bind();
    void UnBind();
    string GetName();
    void   SetName(std::string);
    GLuint GetAttribute(string name);
    GLuint GetUniform(string name);
    
    void AddAttribute(const std::string& attribute);
	void AddUniform(const std::string& uniform);
    void CleanUp();
  
    bool LoadFromFile(GLenum shaderType,std::string source);

    /*
     Those fucntion below use for push the uniform value to the shader
     */
    
    
    void PushUniform(string name, const Texture2D* tex);
    void PushUniform(string name, const CubeTexture* tex);
    void PushUniform(string name, int i);
    void PushUniform(string name, float f);
    void PushUniform2DArray(string name, float num,float * array);
    void PushUniform4DArray(string name, float num,float * array);
    
    void PushUniform(string name, const glm::vec3 &vec3);
    void PushUniform(string name, const glm::mat3 &mat3);
    void PushUniform(string name, const glm::mat4 &mat4);
    void PushUniform(string name, bool b);
    void PushUniform(string name, const glm::vec4 &vec4);
    
    GLuint operator [](const string& uniform);
    
};
#endif /* defined(__CS539_SHUAI_SONG__Shader__) */
