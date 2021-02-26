#include "GameScreenLevel1.h"

#include <iostream>
#include <memory>


#include "Collisions.h"
#include "Texture2D.h"
#include "PowBlock.h"

bool GameScreenLevel1::SetUpLevel()
{
    // Initialise screen shake variables
    m_screen_shaking = false;
    m_shake_time = SCREEN_SHAKE_DURATION;
    m_wobble = 0.0f;
    m_background_yPos = 0.0f;
    
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

    // Create characters and POW block
    m_character_mario = new CharacterMario(m_renderer, Vector2D(64, 300), m_level_map);
    m_character_luigi = new CharacterLuigi(m_renderer, Vector2D(256, 280), m_level_map);
    m_pow_block = new PowBlock(m_renderer, m_level_map);
    
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
    delete m_pow_block;
}

void GameScreenLevel1::Render()
{
    // Draw background texture
    m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

    // Draw characters and POW block
    m_character_mario->Render();
    m_character_luigi->Render();
    m_pow_block->Render();

    // RenderDebugGrid();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
    m_character_mario->Update(deltaTime, e);
    m_character_luigi->Update(deltaTime, e);
    UpdatePOWBlock();

    if (m_screen_shaking)
    {
        m_shake_time -= deltaTime;
        m_wobble++;
        m_background_yPos = sin(m_wobble);
        m_background_yPos *= 3.0f;

        if (m_shake_time <= 0.0f)
        {
            m_screen_shaking = false;
            m_shake_time = 0.0f;
            m_background_yPos = 0.0f;
        }
    }
}


void GameScreenLevel1::UpdatePOWBlock()
{
    bool isColliding = Collisions::Instance()->Box(m_character_mario->GetCollisionBox(), m_pow_block->GetCollisionBox());

    if (isColliding && m_pow_block->IsAvailable() && m_character_mario->IsJumping())
    {
        DoScreenShake();
        m_pow_block->TakeHit();
        m_character_mario->CancelJump();
    }
}

void GameScreenLevel1::DoScreenShake()
{
    m_screen_shaking = true;
    m_shake_time = SCREEN_SHAKE_DURATION;
    m_wobble = 0.0f;
}

void GameScreenLevel1::RenderDebugGrid()
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            switch (m_level_map->GetTileAt(j, i))
            {
            case 0:
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
                break;
            case 1:
                SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
                break;
            default:
                SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
                break;
            }
            SDL_Rect current_rect = {
                i * TILE_WIDTH,
                j * TILE_HEIGHT,
                TILE_WIDTH,
                TILE_HEIGHT
            };
            
            SDL_RenderDrawRect(m_renderer, &current_rect);
        }
    }
}
