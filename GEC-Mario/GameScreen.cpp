#include "GameScreen.h"

#include <iostream>

GameScreen::GameScreen(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session) :
    m_renderer(renderer),
    m_audio_manager(audio_manager),
    m_session(session),
    m_bgm(nullptr)
{
}

GameScreen::~GameScreen()
{
    if (m_bgm != nullptr)
    {
        m_audio_manager->FreeMusic(m_bgm);
    }
    m_renderer = nullptr;
}


bool GameScreen::SetBGM(std::string path)
{
    if (m_audio_manager->IsMusicPlaying())
    {
        m_audio_manager->StopMusic();
    }
    
    if (m_bgm != nullptr)
    {
        m_audio_manager->FreeMusic(m_bgm);
    }
    
    m_bgm = m_audio_manager->LoadMusic(path);
    if (m_bgm == nullptr)
    {
        std::cout << "Failed to load background audio!" << std::endl;
        return false;
    }
    m_audio_manager->PlayMusic(m_bgm, -1);
    return true;
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}
