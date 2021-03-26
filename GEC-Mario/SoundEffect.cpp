#include "SoundEffect.h"


SoundEffect::SoundEffect(AudioManager* audio_manager, std::string path, int preferred_channel)
{
    m_audio_manager = audio_manager;
    m_last_channel = -1;
    m_preferred_channel = preferred_channel;

    m_sound = audio_manager->LoadSound(path);
}

SoundEffect::~SoundEffect()
{
    Stop();
    m_audio_manager->FreeSound(m_sound);
    m_audio_manager = nullptr;
    m_sound = nullptr;
}

void SoundEffect::Play(int loops)
{
    if (IsLoaded())
    {
        m_last_channel = m_audio_manager->PlaySound(m_sound, loops, m_preferred_channel);
    }
}

void SoundEffect::Stop()
{
    if (m_last_channel > -1 && m_audio_manager->IsChannelPlaying(m_last_channel))
    {
        m_audio_manager->StopChannel(m_last_channel);
    }
}
