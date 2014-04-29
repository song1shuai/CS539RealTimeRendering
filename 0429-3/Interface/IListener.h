//
//  IListener.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/2/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_IListener_h
#define CS539_SHUAI_SONG_IListener_h
#include <SDL2/SDL.h>
#include "EventBus.h"
#include <string>
#include "EventBus.h"
//class IEvent;
//class IListener
//{
//private :
//    std::string EventType;
//    
//public:
//    
//    virtual void OnEvent(IEvent *e)=0;
//    virtual void RegisterListener(IListener* listener)=0;
//
//    virtual void RemoveListener(IListener* ob)=0;
// 
//};
//
//class KeyBoardListener:public IListener
//{
//    
//protected:
//    
//    
//    const Uint8*    _keyState;
//    KeyBoardListener()
//    {
//      _keyState = SDL_GetKeyboardState(NULL);
//    }
//public:
//    void OnEvent(IEvent *e)
//    {
//        OnkeyBoardEvent();
//    }
//    virtual void OnkeyBoardEvent()=0;
//    
//};
//
//class IMouseListener:public IListener
//{
//    void OnEvent(IEvent *e)
//    {
//        OnMouseEvent();
//    }
//    virtual void OnMouseEvent()=0;
//    
//};


#endif
