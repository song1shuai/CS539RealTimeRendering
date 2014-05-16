//
//  ITickable.h
//  CS539_SHUAI_SONG
//
//  Created by shuai song on 3/4/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_ITickable_h
#define CS539_SHUAI_SONG_ITickable_h
class ITickable
{
// the interface use for update
public:
    virtual void Tick(float dt)=0;
};


#endif
