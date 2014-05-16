//
//  Cube.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/14/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Cube.h"
void Cube::Draw()
{
    
    glBindVertexArray(this->_vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
    glBindVertexArray(0);

}
void Cube::InitVAO()
{
    float size = 5.0;
    float _size2 = size / 2.0f;
    
    float v[24*3] = {
        // Front
        -_size2, -_size2, _size2,
        _size2, -_size2, _size2,
        _size2,  _size2, _size2,
        -_size2,  _size2, _size2,
        // Right
        _size2, -_size2, _size2,
        _size2, -_size2, -_size2,
        _size2,  _size2, -_size2,
        _size2,  _size2, _size2,
        // Back
        -_size2, -_size2, -_size2,
        -_size2,  _size2, -_size2,
        _size2,  _size2, -_size2,
        _size2, -_size2, -_size2,
        // Left
        -_size2, -_size2, _size2,
        -_size2,  _size2, _size2,
        -_size2,  _size2, -_size2,
        -_size2, -_size2, -_size2,
        // Bottom
        -_size2, -_size2, _size2,
        -_size2, -_size2, -_size2,
        _size2, -_size2, -_size2,
        _size2, -_size2, _size2,
        // Top
        -_size2,  _size2, _size2,
        _size2,  _size2, _size2,
        _size2,  _size2, -_size2,
        -_size2,  _size2, -_size2
    };
    
    float n[24*3] = {
        // Front
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Right
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Back
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        // Left
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // Bottom
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        // Top
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    float tex[24*2] = {
        // Front
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Right
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Back
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Left
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Bottom
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Top
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    
    GLuint el[] = {
        0,1,2,0,2,3,
        4,5,6,4,6,7,
        8,9,10,8,10,11,
        12,13,14,12,14,15,
        16,17,18,16,18,19,
        20,21,22,20,22,23
    };
    
    glGenVertexArrays( 1, &_vao );
    glBindVertexArray(_vao);
    
    unsigned int handle[4];
    glGenBuffers(4, handle);
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), v, GL_STATIC_DRAW);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 2 * sizeof(float), tex, GL_STATIC_DRAW);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(1);  // texture coords
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), n, GL_STATIC_DRAW);
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(2);  // Vertex normal
    

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), el, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}