//
//  sound.h
//  CS539_SHUAI_SONG
//
//  Created by kiya on 4/20/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#ifndef CS539_SHUAI_SONG_sound_h
#define CS539_SHUAI_SONG_sound_h
#include "Engine.h"
#include<SDL2_mixer/SDL_mixer.h>

class sound
{
private:
    bool Running;
    Mix_Music *music;
    bool playmusic;
    bool pausemusic;
    bool playSoundEffect;

public:
    sound();
    ~sound();
    bool Init();
    bool LoadContent();
    void Play();
    void OnRender();
    void Cleanup();
    
};
#endif
