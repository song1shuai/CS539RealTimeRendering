//
//  Mesh3D.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/7/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "Mesh3D.h"
Mesh3DUnit::Mesh3DUnit()
{
    _vbo= -1;
    _ibo =-1;
    _numIndices=0;
    _materialIndex=0;
    
    
}
Mesh3DUnit::~Mesh3DUnit()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ibo);
}
void Mesh3DUnit::InitVAO()
{
   
    

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    _numIndices = (int)_indices.size();
    
   // std::cout <<endl<<_numIndices;
    
    
    glGenBuffers(1, &_vbo);
  	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _numIndices, &_indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)32);
    
    glBindVertexArray(0);
    
}

void Mesh3DUnit::Draw()
{
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


bool Mesh3D::LoadFromFile(const std::string &source)
{
    
    std::ifstream in(source.c_str());
    
    if(in.fail())
    {
        in.close();
        std::cout<<"Couldn't open file:"<<source.c_str()<<endl;
    }
    else
    {
        in.close();
    }
    
    Assimp::Importer importer;
   const aiScene*  scene = importer.ReadFile( source.c_str(),
                                              aiProcess_Triangulate |
                                              aiProcess_GenSmoothNormals |
                                              aiProcess_FlipUVs|
                                              aiProcess_CalcTangentSpace
                                             );
  
    if (!scene)
    {
        printf("%s\n", importer.GetErrorString());
        return false;
    }
    
    
    return InitFromScene(scene, source);
}

void Mesh3D::Draw()
{


    for (int i=0; i<_units.size(); i++)
    {
        _units[i].Draw();
    }
    if (BoundingBox::IsDebugDraw)
    {
        _boundingBox->Draw();
    }
    
    
}
void Mesh3D::InitVAO()
{
    
    this->_material->Init();

    if (BoundingBox::IsDebugDraw)
    {
        _boundingBox = new BoundingBox();
        
        
        for (int i=0; i<_units.size(); i++)
        {
            _units[i].InitVAO();
            _boundingBox->GreatFromVertex(_units[i]._vertices);
        }
        
        
        _boundingBox->InitVAO();
        
        return;
    }
    
    
    for (int i=0; i<_units.size(); i++)
    {
        _units[i].InitVAO();
        
    }
    
    
}
bool Mesh3D::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
    _units.resize(pScene->mNumMeshes);
    _textures.resize(pScene->mNumMaterials);
    
    
    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < _units.size() ; i++)
    {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        ReadMesh(i, paiMesh);
    }
    
    return InitMaterials(pScene, Filename);
}

void Mesh3D::ReadMesh(unsigned int Index, const aiMesh* paiMesh)
{
    _units[Index]._materialIndex = paiMesh->mMaterialIndex;
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    
    
    //get the vertex array of rhis unit
    
    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++)
    {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        const aiVector3D* pTangent  = &(paiMesh->mTangents[i]);
        
        Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
                 glm::vec2(pTexCoord->x, pTexCoord->y),
                 glm::vec3(pNormal->x, pNormal->y, pNormal->z),
                 glm::vec3(pTangent->x, pTangent->y, pTangent->z)
                 );
        
        //Vertices.push_back(v);
        _units[Index]._vertices.push_back(v);
    }
    std::cout<<endl<<_units[Index]._vertices.size()<<endl;
    
    //get the Indices of this unit
    
    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++)
    {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);

        
        
         _units[Index]._indices.push_back(Face.mIndices[0]);
         _units[Index]._indices.push_back(Face.mIndices[1]);
         _units[Index]._indices.push_back(Face.mIndices[2]);
        
        
    }
    
}
bool Mesh3D::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;
    
    if (SlashIndex == std::string::npos)
    {
        Dir = ".";
    }
    else if (SlashIndex == 0)
    {
        Dir = "/";
    }
    else
    {
        Dir = Filename.substr(0, SlashIndex);
    }
    
    bool Ret = true;
    
    
    Mesh3DMaterial * mesh3DMateraial= new Mesh3DMaterial();
    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++)
    {
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        
        //_textures[i] = NULL;
        
        
        
        // Set diffuse testure;
        
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString Path;
            
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE,
                                      0, &Path, NULL, NULL
                                      , NULL, NULL, NULL)
                                    == AI_SUCCESS)
            {
                 std::string FullPath = Dir + "/" + Path.data;
                Texture2D* testure =Texture2D::CreateNextUnit();
                
                if (!testure->Load(FullPath.c_str()))
                {

                    delete testure;
                    Ret = false;
                }
                else
                {
                    mesh3DMateraial->SetDiff(testure);

                }
            }
            
        }
        
        //set specular
        if (pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
        {
            aiString Path;
            
            if (pMaterial->GetTexture(aiTextureType_SPECULAR,
                                      0, &Path, NULL, NULL
                                      , NULL, NULL, NULL)
                == AI_SUCCESS)
            {
                std::string FullPath = Dir + "/" + Path.data;
                Texture2D* testure =Texture2D::CreateNextUnit();
               // testure->Load(FullPath.c_str());
                
                if (!testure->Load(FullPath.c_str()))
                {
                    delete testure;
                    Ret = false;
                }
                else
                {
                    mesh3DMateraial->SetSpec(testure);
                }
            }
        }
        
        // set normal texture
        if (pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0)
        {
            aiString Path;
            
            if (pMaterial->GetTexture(aiTextureType_NORMALS,
                                      0, &Path, NULL, NULL
                                      , NULL, NULL, NULL)
                == AI_SUCCESS)
            {
                std::string FullPath = Dir + "/" + Path.data;
                
             Texture2D* testure =Texture2D::CreateNextUnit();
                
               // testure->Load(FullPath.c_str());
                
                if (!testure->Load(FullPath.c_str()))
                {
                    delete testure;
                    Ret = false;
                }
                else
                {
                    mesh3DMateraial->SetNorml(testure);
                }
            }
        }
        
        // set alpha
        
        if (pMaterial->GetTextureCount(aiTextureType_OPACITY) > 0)
        {
            aiString Path;
            
            if (pMaterial->GetTexture(aiTextureType_OPACITY,
                                      0, &Path, NULL, NULL
                                      , NULL, NULL, NULL)
                == AI_SUCCESS)
            {
                std::string FullPath = Dir + "/" + Path.data;
                
                Texture2D* testure =Texture2D::CreateNextUnit();
                
                
                if (!testure->Load(FullPath.c_str()))
                {
                    
                    delete testure;
                    Ret = false;
                }
                else
                {
                    
                    mesh3DMateraial->SetAlpha(testure);

               
                }
            }
        }

    }
    
    this->_material= mesh3DMateraial;

    return Ret;
        

}
void Mesh3D::Tick(float dt)//let the eagle fly around a circle
{
    
    _tickTime+=0.01;
    //    cout<<"_tickTime "<<_tickTime<<endl;
    this->sceneNode.SetPosition(glm::vec3(210*sin(_tickTime)*dt+15,25,200*cos(_tickTime)*dt));
    //_tickTime=_tickTime;
}
Mesh3D::~Mesh3D()
{
    delete _material;
}
 Mesh3D* Mesh3D::Clone()
{
    return new  Mesh3D(*this);
}