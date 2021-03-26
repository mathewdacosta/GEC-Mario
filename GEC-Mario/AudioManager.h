#pragma once

#include <SDL_mixer.h> // reference: https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html
#include <string>
#include <vector>

class AudioManager
{
private:
    bool m_initialised;
    std::vector<Mix_Music*> m_loaded_music;
    std::vector<Mix_Chunk*> m_loaded_chunks;

public:
    AudioManager();
    ~AudioManager();
    
    bool Setup();
    
    Mix_Music* LoadMusic(std::string path);
    void FreeMusic(Mix_Music* music);
    
    void PlayMusic(Mix_Music* music, int loops);
    bool IsMusicPlaying();
    void StopMusic();
    
    Mix_Chunk* LoadSound(std::string path);
    void FreeSound(Mix_Chunk* music);

    int PlaySound(Mix_Chunk* sound, int loops, int channel = -1, int duration = -1);
    bool IsChannelPlaying(int channel);
    void StopChannel(int channel);
};
