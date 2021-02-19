#include "GameScreenLevel1.h"

#include <iostream>
#include <memory>


#include "Collisions.h"
#include "Texture2D.h"

bool GameScreenLevel1::SetUpLevel()
{
    // Initialise level map to nullptr
    m_level_map = nullptr;
    // Load background texture
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
    {
        std::cout << "Failed to load background texture!" << std::endl;
        return false;
    }

    // Set level map
    SetLevelMap();

    // Create character
    m_character_mario = new CharacterMario(m_renderer, Vector2D(64, 300), m_level_map);
    m_character_luigi = new CharacterLuigi(m_renderer, Vector2D(256, 280), m_level_map);
    
    return true;
}


void GameScreenLevel1::SetLevelMap()
{
    // Define level map
    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Delete old map if still exists
    if (m_level_map != nullptr)
    {
        delete m_level_map;
    }

    // Set new map
    m_level_map = new LevelMap(map);
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

    if (Collisions::Instance()->Circle(m_character_mario, m_character_luigi))
    {
	    std::cout << "CIRCLE HIT" << std::endl;
    }

    if (Collisions::Instance()->Box(m_character_mario->GetCollisionBox(), m_character_luigi->GetCollisionBox()))
    {
        std::cout << "BOX HIT" << std::endl;
    }
}
