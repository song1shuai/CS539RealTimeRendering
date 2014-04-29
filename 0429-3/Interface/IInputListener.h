//
//  IInputListener.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_IInputListener_h
#define CS539_SHUAI_SONG_IInputListener_h
#include <SDL2/SDL.h>

class IInputListener
{

public:

    virtual void OnInput(float dt)=0;

};

//class IInput
//{
//    virtual void RegisterListener(IInputListener *listener)=0;
//    virtual void RemoveListener(IInputListener *listener)=0;
//    virtual void NotifyListener(float dt)=0;
//
//};

class IkeyBoardListener:public IInputListener
{
private:
    const Uint8*    _keyState;
protected:
    int  _x;
    int  _y;
    
    
public:
    IkeyBoardListener()
    {
        _keyState = SDL_GetKeyboardState(NULL);
    }
    
    bool isKeyDown(SDL_Scancode key)
    {
        if (_keyState!=0)
        {
            return _keyState[key]==1;
        }
        
        return false;
    }
    virtual void OnInput(float dt)
    {
        Onkeyboard(dt);
        //OnMouse(dt);
    }
    //virtual void OnMouse(float dt)=0;
    void GetRelateMousePosition()
    {
        SDL_GetRelativeMouseState( &_x, &_y);
    }
   virtual void Onkeyboard(float dt)=0;
};

class IMouseListener:public IInputListener
{
protected:
   int  _x;
   int  _y;
public:
    virtual void OnInput(float dt)
    {
        OnMouse(dt);
    }
    virtual void OnMouse(float dt)=0;
    void GetRelateMousePosition()
    {
        SDL_GetRelativeMouseState( &_x, &_y);
    }
};


#endif
