//
//  Plane.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/12/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Plane.h"
Plane::Plane(float size, int xdivs, int zdivs, float smax, float tmax)
{
    _xsize=size;
    _zsize=size;
    _xdivs=xdivs;
    _zdivs=zdivs;
    _smax=smax;
    _tmax=tmax;
}
void Plane::Draw()
{
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
    glBindVertexArray(0);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    
}
void Plane::InitVAO()
{
    if (_material!=NULL)
    {
        //_material->Init();
    }

    faces = _xdivs * _zdivs;
    _vertices.reserve((_xdivs + 1)*((_zdivs + 1)));
    _indices.resize(6 * _xdivs * _zdivs);
    
    // float * t = new float[3 * (_xdivs + 1) * (_zdivs + 1)];
    
    float x2 = _xsize / 2.0f;
    float z2 = _zsize / 2.0f;
    
    float iFactor = (float)_zsize / _zdivs;
    float jFactor = (float)_xsize / _xdivs;
    
    
    float x, z;
    int k=0;
    for( int i = 0; i <= _zdivs; i++ ) {
        z = iFactor * i - z2;
        for( int j = 0; j <= _xdivs; j++ ) {
            x = jFactor * j - x2;
            Vertex newVertex;
            
            
            newVertex._pos.x=x;
            newVertex._pos.y=0.0;
            newVertex._pos.z=z;
            
            
            newVertex._normal.x=0.0;
            newVertex._normal.y=1.0;
            newVertex._normal.z=0.0;
            
            newVertex._tex.x=j;
            newVertex._tex.y=i;
            
            _vertices.push_back(newVertex);
            
            k++;
        }
    }
    
    unsigned int rowStart, nextRowStart;
    int index = 0;
    for( int i = 0; i < _zdivs; i++ ) {
        rowStart = i * (_xdivs+1);
        nextRowStart = (i+1) * (_xdivs+1);
        for( int j = 0; j < _xdivs; j++ ) {
            
            _indices[index]   = rowStart + j;
            _indices[index+1] = nextRowStart + j;
            _indices[index+2] = nextRowStart + j + 1;
            _indices[index+3] = rowStart + j;
            _indices[index+4] = nextRowStart + j + 1;
            _indices[index+5] = rowStart + j + 1;
            
            index += 6;
        }
    }
    
    
    
    
    unsigned int handle[4];
    glGenBuffers(4, handle);
    
	glGenVertexArrays( 1, &_vao );
    glBindVertexArray(_vao);
    
    
    glGenBuffers(1, &_vbo);
  	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);
    
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*_indices.size(), &_indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)32);
    
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    
}
