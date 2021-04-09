#include "AudioManager.h"

#include <iostream>
#include <ostream>
#include "constants.h"

AudioManager::AudioManager()
{
    m_initialised = false;
    m_loaded_music = {};
}

AudioManager::~AudioManager()
{
    if (!m_initialised) return;

    for (int i = 0; i < m_loaded_music.size(); i++)
    {
        FreeMusic(m_loaded_music[i]);
    }
    
    Mix_CloseAudio();
    Mix_Quit();
}

bool AudioManager::Setup()
{
    if (Mix_Init(0) < 0 || Mix_OpenAudio(MIXER_FREQUENCY, MIX_DEFAULT_FORMAT, MIXER_OUTPUT_CHANNELS, MIXER_CHUNK_SIZE) < 0)
    {
        std::cout << "Could not initialise mixer. Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Allocate mixing channels
    Mix_AllocateChannels(MIXER_CHANNELS);
    
    m_initialised = true;
    return true;
}

Mix_Music* AudioManager::LoadMusic(std::string path)
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
        m_loaded_music.push_back(loadedAudio);
    }
    return loadedAudio;
}

void AudioManager::FreeMusic(Mix_Music* music)
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
    for (int i = 0; i < m_loaded_music.size(); i++)
    {
        if (m_loaded_music[i] == music)
        {
            m_loaded_music.erase(m_loaded_music.begin() + i);
        }
    }
}

void AudioManager::PlayMusic(Mix_Music* music, int loops)
{
    #ifdef DEBUG_AUDIO_DISABLE_MUSIC
    return;
    #endif
    
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


Mix_Chunk* AudioManager::LoadSound(std::string path)
{
    if (!m_initialised)
    {
        std::cout << "Tried to load audio before mixer init (path: " << path << ")" << std::endl;
        return nullptr;
    }
    
    Mix_Chunk* loadedChunk = Mix_LoadWAV(path.c_str());
    if (loadedChunk == nullptr)
    {
        std::cout << "Failed to load audio chunk (path: " << path << "). Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        // Track any audio that we load
        m_loaded_chunks.push_back(loadedChunk);
    }
    return loadedChunk;
}

void AudioManager::FreeSound(Mix_Chunk* sound)
{
    if (!m_initialised)
    {
        std::cout << "Tried to free audio before mixer init (music address: " << sound << ")" << std::endl;
    }
    if (sound == nullptr)
    {
        std::cout << "Cannot free null audio" << std::endl;
        return;
    }
    
    Mix_FreeChunk(sound);

    // Remove from known loaded audio
    for (int i = 0; i < m_loaded_chunks.size(); i++)
    {
        if (m_loaded_chunks[i] == sound)
        {
            m_loaded_chunks.erase(m_loaded_chunks.begin() + i);
        }
    }
}

int AudioManager::PlaySound(Mix_Chunk* sound, int loops, int channel, int duration)
{
    #ifdef DEBUG_AUDIO_DISABLE
    return -1;
    #endif
    
    if (!m_initialised)
    {
        std::cout << "Tried to play sound before mixer init (sound address: " << sound << ")" << std::endl;
        return -1;
    }
    if (sound == nullptr)
    {
        std::cout << "Cannot play null sound" << std::endl;
        return -1;
    }

    return Mix_PlayChannelTimed(channel, sound, loops, duration);
}

bool AudioManager::IsChannelPlaying(int channel)
{
    if (!m_initialised)
    {
        std::cout << "Tried to check playing channels before mixer init" << std::endl;
        return false;
    }
    
    return Mix_Playing(channel);
}

void AudioManager::StopChannel(int channel)
{
    Mix_HaltChannel(channel);
}
