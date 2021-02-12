#include "GameScreenLevel1.h"

#include <iostream>
#include <memory>

#include "Texture2D.h"

bool GameScreenLevel1::SetUpLevel()
{
    // Load background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
    {
        std::cout << "Failed to load background texture!" << std::endl;
        return false;
    }

    // Create character
    m_character_mario = new CharacterMario(m_renderer, Vector2D(64, 300));
    m_character_luigi = new CharacterLuigi(m_renderer, Vector2D(64, 300));
    
    return true;
}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
    SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
    delete m_background_texture;
    delete m_character_mario;
    delete m_character_luigi;
}

void GameScreenLevel1::Render()
{
    // Draw background texture
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

    // Draw characters
    m_character_mario->Render();
    m_character_luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
    m_character_mario->Update(deltaTime, e);
    m_character_luigi->Update(deltaTime, e);
}
