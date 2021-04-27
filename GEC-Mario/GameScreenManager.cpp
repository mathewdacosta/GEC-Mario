#include "GameScreenManager.h"

#include <iostream>

#include "GameScreen.h"
#include "GameScreenError.h"
#include "GameScreenGameOver.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, AudioManager* audio_manager, GameSession* session, Screen start_screen) :
    m_renderer(renderer),
    m_audio_manager(audio_manager),
    m_session(session),
    m_current_screen(nullptr),
    m_next_screen(start_screen),
    m_screen_queued(false)
{
    ChangeScreen(start_screen);
}

GameScreenManager::~GameScreenManager()
{
    m_renderer = nullptr;
    
    delete m_current_screen;
    m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
    if (!m_screen_queued)
    {
        m_current_screen->Render();
    }
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
    if (m_screen_queued)
    {
        ChangeScreen(m_next_screen);
        m_screen_queued = false;
    }
    
    m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(Screen new_screen)
{
    // Clear up old screen
    if (m_current_screen != nullptr)
    {
        delete m_current_screen;
    }

    switch (new_screen)
    {
    case Screen::INTRO:
        m_current_screen = new GameScreenIntro(m_renderer, m_audio_manager, this, m_session);
        break;
    case Screen::LEVEL_1:
        m_current_screen = new GameScreenLevel1(m_renderer, m_audio_manager, this, m_session);
        break;
    case Screen::LEVEL_2:
        m_current_screen = new GameScreenLevel2(m_renderer, m_audio_manager, this, m_session);
        break;
    case Screen::GAME_OVER:
        m_current_screen = new GameScreenGameOver(m_renderer, m_audio_manager, m_session);
        break;
    case Screen::ERROR:
    default:
        m_current_screen = new GameScreenError(m_renderer, m_audio_manager, m_session);
        break;
    }

	if (!m_current_screen->Setup())
	{
        std::cout << "Screen setup failed!" << std::endl;
	    QueueScreen(Screen::ERROR);
	}
}


void GameScreenManager::QueueScreen(Screen next_screen)
{
    m_next_screen = next_screen;
    m_screen_queued = true;
}
