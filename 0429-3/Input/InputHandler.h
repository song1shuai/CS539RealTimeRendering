//
//  InputHandler.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef __CS539_SHUAI_SONG__InputHandler__
#define __CS539_SHUAI_SONG__InputHandler__

#include <iostream>
#include "IInputListener.h"
#include <list>
#include <SDL2/SDL.h>

class InputHandler
{
    
/*
 for now, the inputhandler just use for pool out sdl event 
 */

private:
 
    std::list<IInputListener* > _listenerList;
    std::list<IInputListener* >::iterator _iter;
   
    std::list<IInputListener* > _MlistenerList;
    std::list<IInputListener* >::iterator _Miter;
    
    float _dt;
    
    
    /*
     This is a Singleton
     */
    
    static InputHandler _instance;
    
public:
    InputHandler(){};
    
    static InputHandler &GetInstance();
 
    void RegisterListener(IInputListener *listener);
 
    void RegisteMouseListener(IInputListener *listener);
    void RemoveMouseListener(IInputListener *listener);
    
    void RemoveListener(IInputListener *listener);
 
    void NotifyListener(float dt);
    void NotifyMouseListener(float dt);
 
    void Tick(float dt);
    
};

#endif /* defined(__CS539_SHUAI_SONG__InputHandler__) */
