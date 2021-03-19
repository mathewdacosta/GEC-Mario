#include "AudioManager.h"

#include <iostream>
#include <ostream>


AudioManager::AudioManager()
{
    m_initialised = false;
    m_loaded_audio = {};
}

AudioManager::~AudioManager()
{
    if (!m_initialised) return;

    for (int i = 0; i < m_loaded_audio.size(); i++)
    {
        FreeAudio(m_loaded_audio[i]);
    }
    
    Mix_CloseAudio();
    Mix_Quit();
}

bool AudioManager::Setup()
{
    if (Mix_Init(0) < 0 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Could not initialise mixer. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    m_initialised = true;
    return true;
}

Mix_Music* AudioManager::LoadAudio(std::string path)
{
    if (!m_initialised)
    {
        std::cout << "Tried to load audio before mixer init (path: " << path << ")" << std::endl;
        return nullptr;
    }
    
    Mix_Music* loadedAudio = Mix_LoadMUS(path.c_str());
    if (loadedAudio == nullptr)
    {
        std::cout << "Failed to load audio (path: " << path << "). Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        // Track any audio that we load
        m_loaded_audio.push_back(loadedAudio);
    }
    return loadedAudio;
}

void AudioManager::FreeAudio(Mix_Music* music)
{
    if (!m_initialised)
    {
        std::cout << "Tried to free audio before mixer init (music address: " << music << ")" << std::endl;
    }
    if (music == nullptr)
    {
        std::cout << "Cannot free null audio" << std::endl;
        return;
    }
    
    Mix_FreeMusic(music);

    // Remove from known loaded audio
    for (int i = 0; i < m_loaded_audio.size(); i++)
    {
        if (m_loaded_audio[i] == music)
        {
            m_loaded_audio.erase(m_loaded_audio.begin() + i);
        }
    }
}

void AudioManager::PlayMusic(Mix_Music* music, int loops)
{
    if (!m_initialised)
    {
        std::cout << "Tried to play music before mixer init (music address: " << music << ")" << std::endl;
        return;
    }
    if (music == nullptr)
    {
        std::cout << "Cannot play null music" << std::endl;
        return;
    }

    Mix_PlayMusic(music, loops);
}

bool AudioManager::IsMusicPlaying()
{
    if (!m_initialised)
    {
        std::cout << "Tried to check playing music before mixer init" << std::endl;
        return false;
    }
    
    return Mix_PlayingMusic() != 0;
}


void AudioManager::StopMusic()
{
    Mix_HaltMusic();
}
