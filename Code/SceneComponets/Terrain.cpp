//
//  terrain.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/31/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "terrain.h"
void terrain::Draw()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
    
//    for (int i = 0; i < _plants.size(); i++)
//    {
//        _plants[i]->Draw();
//    }
    
    glBindVertexArray(0);
    glDisable(GL_CULL_FACE);
    
}
void terrain::InitVAO()
{
    
    this->GetMaterial()->Init();
    this->CalculateNormals();
    
    
	_vertexCount = (_width - 1) * (_height - 1) * 12;
    _indexCount = _vertexCount;
    
    
    _vertices.reserve(_vertexCount);
    _vertices.resize(_vertexCount);
    
    _indices.reserve(_indexCount);
    _indices.resize(_indexCount);
    
    int i, j, indices[4], pIndex=0;
    
    
    // Generate Index of the heightmap date
 	for(j=0; j<(_height-1); j++)
	{
		for(i=0; i<(_width-1); i++)
		{
			indices[0] = (_height * j) + i;          // Bottom left.
			indices[1] = (_height * j) + (i+1);      // Bottom right.
			indices[2] = (_height * (j+1)) + i;      // Upper left.
			indices[3] = (_height * (j+1)) + (i+1);  // Upper right.
            
            // frist triangles
            

            _indices[pIndex]=indices[2];
            pIndex++;
            //bottom right 1

            _indices[pIndex]=indices[1];
            pIndex++;
            //upper right. 3
            
            _indices[pIndex]=indices[3];
            pIndex++;
            
            
            // Upper left. 2

            _indices[pIndex]=indices[2];
            pIndex++;
            // bottom left  0

            _indices[pIndex]=indices[0];
            pIndex++;
            
            //bottom right 1
            _indices[pIndex]=indices[1];
            
            
            pIndex++;
            
            
        }
    }
    
    
    
    glGenVertexArrays( 1, &_vao );
    glBindVertexArray(_vao);
    
    glGenBuffers(1, &_vbo);
  	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _heightMapData.size(), &_heightMapData[0], GL_STATIC_DRAW);


    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*_indexCount, &_indices[0], GL_STATIC_DRAW);
    
    
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
    
    glBindVertexArray(0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(2);
    
    
    
   // _vertices.clear();
    
}
bool terrain::LoadHightMap(string fileName,int height)
{
    _image =SOIL_load_image(fileName.c_str(), &_width, &_height, 0, SOIL_LOAD_RGB);
    
    if (_image==NULL)
    {
        std::cout<<fileName<<" Load false!!"<<std::endl;
        return false;
        
    }
    
    _heightMapData.resize(_width*_height);
    int k=0;
    float pointHight=0;
    int index=0;
    
    float fTextureU = float(_width)*0.4f;
    float fTextureV = float(_height)*0.4f;
    
    //float fTextureU = 0.1;
    //float fTextureV = 0.1;
    
    for (int y=0; y< _height; y++)
    {
        for (int x=0; x<_width; x++)
        {
            
            float fScaleC = float(y)/float(_height-1);
            float fScaleR = float(x)/float(_width-1);
            
            pointHight=(float)_image[k];
            pointHight=height*((pointHight/255.0f));            //resize y value of the messh
            index =(_height*y+x);
            
            _heightMapData[index]._pos.x=(float)x;
            _heightMapData[index]._pos.y=(float)pointHight;
            _heightMapData[index]._pos.z=(float)y;
            _heightMapData[index]._tex=glm::vec2(fTextureU*fScaleC, fTextureV*fScaleR);
            k+=3;
        }
        
    }

    SOIL_free_image_data(_image);
    _image=NULL;
    
    return  true;
    
}
void terrain::CalculateNormals()
{
    int i, j, indices[3], pIndex=0;
    
    glm::vec3 TmpVector1;
    glm::vec3 TmpVector2;
    
    glm::vec3* normals;
    normals = new glm::vec3[(_height-1) * (_width-1)];
    
    
    
    for(j=0; j<(_height-1); j++)
	{
		for(i=0; i<(_width-1); i++)
		{
            indices[0] = (j * _height) + i;
            indices[1] = (j * _height) + (i+1);
            indices[2]= ((j+1) * _height) + i;
            
            TmpVector1 = _heightMapData[indices[0]]._pos-_heightMapData[indices[2]]._pos;
            TmpVector2 = _heightMapData[indices[0]]._pos-_heightMapData[indices[1]]._pos;
            
            pIndex=(j*(_height-1))+i;
            normals[pIndex] = glm::cross(TmpVector1, TmpVector2);
            
        }
        
    }
    
    
    // smooth normal
    
    glm::vec3 sum=glm::vec3(.0);
    int index,count=0;
    
    for(j=0; j<(_height); j++)
	{
		for(i=0; i<(_width); i++)
		{
            
            sum=glm::vec3(.0);
            count=0;
            // Bottom left
            if (((i-1)>= 0)&&((j-1)>=0))
            {
                index = ((j-1)*(_height-1) + (i-1));
                sum+=normals[index];
                count++;
            }
            //bottom right
            if ((i < _width -1) && ((j-1)>=0))
            {
                index = ((j-1) * (_height-1)) + i;
                sum+= normals[index];
                count++;
            }
            
            // Upper left face.
			if(((i-1) >= 0) && (j < (_height-1)))
			{
				index = (j * (_height-1)) + (i-1);
                
                sum+=normals[index];
				count++;
			}
            
			// Upper right face.
			if((i < (_width-1)) && (j < (_height-1)))
			{
				index = (j * (_height-1)) + i;
                
                sum+=normals[index];
				count++;
			}
            //average normal
            sum/=count;
            sum = glm::normalize(sum);
            index = (j * _height) + i;
            _heightMapData[index]._normal = sum;
            
            //std::cout<<glm::to_string(sum)<<endl;
        }
        
    }
    
    delete [] normals;
    normals = NULL;
    
}
void terrain::GenPlant()
{
    for(int k=0; k<360; k++)
    {
        int x = Random1D(1, _width*_height);
        glm::vec3 p = _heightMapData[x]._pos;
        
        
        Mesh3D* plant;
        
        if (p.y > 10 && p.y < 15)
        {
            continue;
        }
         if (p.y > 0 && p.y < 10)
        {
         
            float tmp = Random1D(1, 8);
            float scale =  Random1D(1, 10);
            if (tmp < 3.0)
            {
                
                 plant=MeshFactory::GetInstance()->GetMesh("bamboo");

                plant->sceneNode.SetScale(glm::vec3(1,scale/10,1));
                plant->sceneNode.SetScale(glm::vec3(scale/5,scale/10,scale/5));
                

            }
            else
            {
                
                plant=MeshFactory::GetInstance()->GetMesh("hightree");
                plant->sceneNode.SetScale(glm::vec3(scale/5,scale/10,scale/5));
            
            
            }
            
        }
        
//        if (tmp%2==0)
//        {
//            plant=MeshFactory::GetInstance()->GetMesh("bamboo");
//        }
//        else
//        {
//            plant=MeshFactory::GetInstance()->GetMesh("grass1");
//        }
        p= glm::vec3(this->sceneNode.GetTransformMatrix()*glm::vec4(p,1.0));
        plant->sceneNode.SetPosition(p);
       // _plants.push_back(plant);
        _plantPos.push_back(p);
        
    }
}