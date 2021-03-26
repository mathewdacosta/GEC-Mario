#pragma once
#include "AudioManager.h"

class SoundEffect
{
private:
    AudioManager* m_audio_manager;
    Mix_Chunk* m_sound;
    int m_last_channel;
    int m_preferred_channel;

public:
    // Creates a sound effect that will use a specific channel. 
    SoundEffect(AudioManager* audio_manager, std::string path, int preferred_channel);
    ~SoundEffect();

    // Play the sound effect.
    void Play(int loops = 0);
    // Stop the sound effect. This may interrupt other sound effects if they share the same channel. 
    void Stop();

    // Change the preferred channel.
    void SetPreferredChannel(int channel) { this->m_preferred_channel = channel; }
    // Check whether the sound loaded correctly.
    bool IsLoaded() { return this->m_sound != nullptr; }
};
