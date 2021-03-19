#pragma once

#include <SDL_mixer.h>
#include <string>
#include <vector>

class AudioManager
{
private:
    bool m_initialised;
    std::vector<Mix_Music*> m_loaded_audio;

public:
    AudioManager();
    ~AudioManager();
    
    bool Setup();
    
    Mix_Music* LoadAudio(std::string path);
    void FreeAudio(Mix_Music* music);
    
    void PlayMusic(Mix_Music* music, int loops);
    bool IsMusicPlaying();
    void StopMusic();
};
