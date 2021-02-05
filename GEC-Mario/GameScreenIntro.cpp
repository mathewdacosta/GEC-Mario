#include "GameScreenIntro.h"

#include <iostream>
#include "Texture2D.h"

bool GameScreenIntro::SetUpLevel()
{
    // Load background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/test-2.bmp"))
    {
        std::cout << "Failed to load background texture!" << std::endl;
        return false;
    }
    return true;
}

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
    SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{
    delete m_background_texture;
}

void GameScreenIntro::Render()
{
    // Draw background texture
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
}
