//
//  Shader.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 2/16/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Shader.h"
Shader::Shader()
{

    _totalShaders=0;
	_shaders[VERTEX_SHADER]=0;
	_shaders[FRAGMENT_SHADER]=0;
	_shaders[GEOMETRY_SHADER]=0;
    _attributes.clear();
    _uniformLocations.clear();
    
}
void Shader::SetName(std::string name)
{
    _name=name;
    
}
Shader::~Shader()
{
    CleanUp();
}
bool Shader::LoadFromFile(GLenum shaderType,std::string source)
{
    ifstream fp;
	fp.open(source.c_str(), ios_base::in);
	if(!fp)
    {
         cout<<"Error loading shader: "<<source<<endl;
        return false;
    }
    
    string line;
    string buffer;

    while(getline(fp, line))
    {
        buffer.append(line);
        buffer.append("\r\n");
    }


    const char * tmp = buffer.c_str();
   // std::cout<<buffer<<std::endl;
    
    GLuint shader= glCreateShader (shaderType);
    
    
    glShaderSource(shader, 1, &tmp,NULL );

    //check whether the shader loads fine
    GLint status;
    glCompileShader (shader);
    glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        
        std::cerr << source.c_str() << " failed to compile:" << std::endl;
		GLint  logSize;
	    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog( shader, logSize, NULL, logMsg );
	    std::cerr << logMsg << std::endl;
	    delete [] logMsg;
		int q;
        std::cin >> q;
		exit( EXIT_FAILURE );
    }
    _shaders[_totalShaders++]=shader;
    
    return true;
 
    
}
bool Shader::CreateShaderProgram()
{
    _program = glCreateProgram ();
	if (_shaders[VERTEX_SHADER] != 0)
    {
		glAttachShader (_program, _shaders[VERTEX_SHADER]);
	}
	if (_shaders[FRAGMENT_SHADER] != 0)
    {
		glAttachShader (_program, _shaders[FRAGMENT_SHADER]);
	}
	if (_shaders[GEOMETRY_SHADER] != 0)
    {
		glAttachShader (_program, _shaders[GEOMETRY_SHADER]);
	}
    
	//link and check whether the program links fine
	GLint status;
	glLinkProgram (_program);
	glGetProgramiv (_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
    {
		GLint infoLogLength;
        
		glGetProgramiv (_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog= new GLchar[infoLogLength];
		glGetProgramInfoLog (_program, infoLogLength, NULL, infoLog);
		cerr<<"Link log: "<<infoLog<<endl;
		delete [] infoLog;
        return false;
	}
    

    return true;
}
void Shader::Bind()
{
    glUseProgram(_program);

}
void Shader::UnBind()
{
    
    glUseProgram(0);
}

void Shader::AddAttribute(const std::string& attribute)
{
    _attributes[attribute]= glGetAttribLocation(_program, attribute.c_str());
}
void Shader::AddUniform(const std::string& uniform)
{
    _uniformLocations[uniform] = glGetUniformLocation(_program, uniform.c_str());

}
void Shader::CleanUp()
{
  
    
    _attributes.clear();
    _uniformLocations.clear();
    

}

GLuint Shader::GetAttribute(string attribute)
{
    return _attributes[attribute];
}

GLuint Shader::GetUniform(string uniform)

{
    return _uniformLocations[uniform];
}
string Shader::GetName()
{
    return _name;
}
GLuint Shader::operator [](const string& uniform)
{
    return _uniformLocations[uniform];
}
void Shader::PushUniform(string name, const Texture2D* tex)
{
      glUniform1i(_uniformLocations[name], tex->_texUnit);
}
void Shader::PushUniform(string name, const CubeTexture* tex)
{
    
      glUniform1i(_uniformLocations[name], tex->_texUnit);
    
}
void Shader::PushUniform(string name, int i)
{
    //std::cout<<GL_TEXTURE0<<"!!!!!!!!!!";
     glUniform1i(_uniformLocations[name], i);
}
void Shader::PushUniform(string name, float f)
{
     glUniform1f(_uniformLocations[name], f);
}
//void Shader::PushUniform(string name, float f1, float f2)
//{
//     glUniform2f(_uniformLocations[name], f1, f2);
//}

void Shader::PushUniform(string name, const glm::vec3 &vec3)
{
    glUniform3f(_uniformLocations[name], vec3.x, vec3.y, vec3.z);
}
void Shader::PushUniform(string name, const glm::vec4 &vec4)
{
    glUniform4f(_uniformLocations[name], vec4.x, vec4.y, vec4.z,vec4.w);
}
void Shader::PushUniform(string name, const glm::mat3 &mat3)
{
     glUniformMatrix3fv(_uniformLocations[name], 1, GL_TRUE, &mat3[0][0]);
}
void Shader::PushUniform(string name, const glm::mat4 &mat4)
{
  //  std::cout<<glm::to_string(mat4);
   
    glUniformMatrix4fv(_uniformLocations[name], 1, GL_FALSE, &mat4[0][0]);
    
}
void Shader::PushUniform(string name, bool b)
{
   
    glUniform1i(_uniformLocations[name], b);
}
void Shader::PushUniform2DArray(string name, float num,float * array)
{
    glUniform2fv(_uniformLocations[name],num,array);
}
void Shader::PushUniform4DArray(string name, float num,float * array)
{
    glUniform4fv(_uniformLocations[name],num,array);
}