//
//  BoundingBox.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 4/6/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_BoundingBox_h
#define CS539_SHUAI_SONG_BoundingBox_h

#include "glm.hpp"
#include <vector>
#include "IDrawable.h"
#include "SceneManager.h"


class BoundingBox:public IDrawable
{


    
public:
    static bool IsDebugDraw;
    
    glm::vec3 PLowLeftFront;    //lower left front point
    glm::vec3 PUpRightBack ;      //Up right back point
    BoundingBox()
    {
        // Init the the left front point to a large value;
        PLowLeftFront = glm::vec3(999999.0f, 999999.0f, -999999.0f);
        
        //Init the right back point to a small value
        PUpRightBack  = glm::vec3(-999999.0f, -999999.0f, 999999.0f);
    };
    
     bool IsContainsPoint(const glm::vec3& point)
    {
        return (point.x>=PLowLeftFront.x &&
                point.y>=PLowLeftFront.y &&
                point.z>=PLowLeftFront.z &&
                point.x<=PUpRightBack.x  &&
                point.y<=PUpRightBack.y  &&
                point.z<=PUpRightBack.z);
    }
    
    void GreatFromVertex(std::vector<Vertex> & pos);            // Create a bounding box for vertex struct
    void Draw();                                                // Debug draw the bounding box
    void InitVAO();
    
};

#endif
