#include "GameScreenManager.h"

#include "GameScreen.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS start_screen)
{
    m_renderer = renderer;
    m_current_screen = nullptr;

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
    m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
    m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
    // Clear up old screen
    if (m_current_screen != nullptr)
    {
        delete m_current_screen;
    }

    switch (new_screen)
    {
    case SCREEN_INTRO:
        m_current_screen = new GameScreenIntro(m_renderer);
        break;
    default:
    case SCREEN_LEVEL_1:
        m_current_screen = new GameScreenLevel1(m_renderer);
        break;
        ;
    }
}
