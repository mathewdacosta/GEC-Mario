#include "GameScreenLevel1.h"

#include <iostream>
#include <memory>

#include "Texture2D.h"

bool GameScreenLevel1::SetUpLevel()
{
    // Load background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/test.bmp"))
    {
        std::cout << "Failed to load background texture!" << std::endl;
        return false;
    }

    // Create character
    m_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 300), 50.0f);
    
    return true;
}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
    SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
    delete m_background_texture;
    delete m_character;
}

void GameScreenLevel1::Render()
{
    // Draw background texture
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

    // Draw character
    m_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
    m_character->Update(deltaTime, e);
}
