//
//  BoundingBox.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/7/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "BoundingBox.h"
bool BoundingBox::IsDebugDraw = false;
void BoundingBox::GreatFromVertex(std::vector<Vertex> & vertex)
{
    for (int i = 0; i < vertex.size(); i++)
    {
        
        // Update lower left front corner of BB
        PLowLeftFront.x = fmin(PLowLeftFront.x, vertex[i]._pos.x);
        PLowLeftFront.y = fmin(PLowLeftFront.y, vertex[i]._pos.y);
        PLowLeftFront.z = fmax(PLowLeftFront.z, vertex[i]._pos.z);
        // Update upper right back corner of BB
        PUpRightBack.x = fmax(PUpRightBack.x, vertex[i]._pos.x);
        PUpRightBack.y = fmax(PUpRightBack.y, vertex[i]._pos.y);
        PUpRightBack.z = fmin(PUpRightBack.z, vertex[i]._pos.z);
    }
    
}
void BoundingBox::Draw()
{
    
    if (IsDebugDraw)
    {
    
    Shader *bbshader= ShaderLibrary::GetShader("basic");
    bbshader->Bind();
   
    bbshader->PushUniform("mvp", SceneManager::GetInstance().GetMVPMatrix());
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBindVertexArray(_vao);
	glEnable(GL_PRIMITIVE_RESTART_INDEX);
	glPrimitiveRestartIndex(8);
	glDrawElements(GL_TRIANGLE_STRIP, 29, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
    bbshader->UnBind();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        
    }
}
void BoundingBox::InitVAO()
{

    
    int iIndices[] =
    {
        0, 1, 2, 3, 8, // Front wall
        4, 5, 6, 7, 8, // Back wall
        4, 0, 6, 2, 8, // Left wall
        1, 5, 3, 7, 8, // Right wall
        2, 3, 6, 7, 8, // Top wall
        0, 1, 4, 5     // Bottom wall
    };
    
    glm::vec3 vBoxVertices[] =
	{
		// Front wall of bounding box
		
        PLowLeftFront,
		glm::vec3(PUpRightBack.x, PLowLeftFront.y, PLowLeftFront.z),
		glm::vec3(PLowLeftFront.x, PUpRightBack.y, PLowLeftFront.z),
		glm::vec3(PUpRightBack.x, PUpRightBack.y, PLowLeftFront.z),
        
		// Back wall of bounding box
		glm::vec3(PLowLeftFront.x, PLowLeftFront.y, PUpRightBack.z),
		glm::vec3(PUpRightBack.x, PLowLeftFront.y, PUpRightBack.z),
		glm::vec3(PLowLeftFront.x, PUpRightBack.y, PUpRightBack.z),
		PUpRightBack
	};
    
    
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    GLuint vbo;
    GLuint ibo;
    
    glGenBuffers(1, &vbo);
  	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vBoxVertices), &vBoxVertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iIndices), &iIndices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
    
    
    
}