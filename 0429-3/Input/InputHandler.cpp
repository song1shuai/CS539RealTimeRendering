//
//  InputHandler.cpp
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "InputHandler.h"
InputHandler InputHandler::_instance;
InputHandler &InputHandler::GetInstance()
{
    return _instance;
}
void InputHandler::RegisterListener(IInputListener *listener)
{
    _listenerList.push_back(listener);
}
void InputHandler::RemoveListener(IInputListener *listener)
{
    _listenerList.remove(listener);
}
void InputHandler::NotifyListener(float dt)
{
    for (_iter=_listenerList.begin(); _iter!=_listenerList.end(); _iter++)
    {
        (*_iter)->OnInput(dt);
    }
}
void InputHandler::RegisteMouseListener(IInputListener *listener)
{
    _MlistenerList.push_back(listener);
}
void InputHandler::NotifyMouseListener(float dt)
{
    for (_Miter=_MlistenerList.begin(); _Miter!=_MlistenerList.end(); _Miter++)
    {
        (*_Miter)->OnInput(dt);
    }
    
}
void InputHandler::Tick(float dt)
{
 
    _dt=dt;
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
                NotifyListener(dt);
                break;
            default:
                break;
        }
        
    }
}