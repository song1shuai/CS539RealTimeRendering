//
//  sound.cpp
//  CS539_SHUAI_SONG
//
//  Created by kiya on 4/20/14.
//  Copyright (c) 2014 shuai song. All rights reserved.
//

#include "sound.h"
sound::sound()
{

    Running = true;
    music=NULL;
    playmusic=1;
    pausemusic=0;
    playSoundEffect=0;
}
bool sound::Init()
{

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }
    
    return true;
}
bool sound::LoadContent()
{
    //std::cout<<"loading Music"<<endl;
    music = Mix_LoadMUS( "forest.mp3" );
    if( music == NULL )
    {
    //std::cout<<"couldn't load music"<<endl;
        return false;
    }

    if( music == NULL )
    {
        //std::cout<<"couldn't load gunshot"<<endl;
        return false;
    }
    return 1;
}

void sound::Play()
{
    if( Mix_PlayingMusic() == 0 && playmusic==1)
    {
        Mix_PlayMusic( music, -1 );
        playmusic=0;
    }
    if( Mix_PlayingMusic() == 1 && playmusic==1)
    {
        Mix_HaltMusic();
        playmusic=0;
    }
    if (Mix_PlayingMusic()==1 && pausemusic==1)
    {
        Mix_PauseMusic();
    }
    if (Mix_PausedMusic()==1 && pausemusic==0)
    {
        Mix_ResumeMusic();
    }
}
void sound::Cleanup()
{
    Mix_FreeMusic( music );

    Mix_CloseAudio();
    

}
sound::~sound()
{
    Cleanup();
}