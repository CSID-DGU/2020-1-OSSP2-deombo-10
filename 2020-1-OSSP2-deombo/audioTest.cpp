#include<iostream>
#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
   

    Mix_Music *songName;
    Mix_Chunk *soundEffect;
    songName=Mix_LoadMUS("assets/514241__tyops__dramatic-urban-beat.mp3");
    soundEffect=Mix_LoadWAV("assets/382735__schots__gun-shot.aiff");
 
    Mix_PlayMusic(songName,-1);
    Mix_VolumeMusic(128);
    while(1)
    {

    };
     Mix_CloseAudio();
}