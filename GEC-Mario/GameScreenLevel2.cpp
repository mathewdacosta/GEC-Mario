#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, AudioManager* audio_manager, GameScreenManager* screen_manager, GameSession* session) :
    GameScreenLevelBase(renderer, audio_manager, screen_manager, session, "Images/Level2_BG.png", "Images/Level2_Overlay.png", "Images/Level2_Tiles.png", "Audio/Music/MarioUnderworld.mp3", "Levels/02.txt")
{
}

bool GameScreenLevel2::SetUpLevel()
{
    if (!GameScreenLevelBase::SetUpLevel())
    {
        return false;
    }

    // Reset score
    m_session->score = 0;

    // Set up spawner variables
    m_enemy_spawn_side = 0;
    m_enemy_spawn_timer = LEVEL_2_SPAWNER_DELAY;
    
    return true;
}

void GameScreenLevel2::SetUpEntities()
{
    CreateMario(Vector2D(64, 320));
    CreateLuigi(Vector2D(416, 320));

    CreateKoopa(Vector2D(150, 32), Facing::RIGHT, KOOPA_SPEED);
    CreateKoopa(Vector2D(325, 32), Facing::LEFT, KOOPA_SPEED);
}

void GameScreenLevel2::UpdateSpawners(float deltaTime)
{
    m_enemy_spawn_timer -= deltaTime;
    if (m_enemy_spawn_timer <= 0.0f)
    {
        Vector2D position;
        Facing direction;
        if (m_enemy_spawn_side == 0)
        {
            position = LEVEL_2_SPAWNER_POSITION_0;
            direction = Facing::RIGHT;
        }
        else
        {
            position = LEVEL_2_SPAWNER_POSITION_1;
            direction = Facing::LEFT;
        }

        CreateKoopa(position, direction, KOOPA_SPEED);

        m_enemy_spawn_side = (m_enemy_spawn_side + 1) % 2;
        m_enemy_spawn_timer = LEVEL_2_SPAWNER_DELAY;
    }
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
    m_character_mario->Update(deltaTime, e);
    m_character_luigi->Update(deltaTime, e);
    UpdateEnemies(deltaTime, e);
    UpdateCoins(deltaTime, e);
    UpdateSpawners(deltaTime);
    UpdateScoreText();
    CheckPlayersAlive();

    if (m_screen_shaking)
    {
        m_shake_time -= deltaTime;
        m_wobble++;
        m_background_y_pos = sin(m_wobble);
        m_background_y_pos *= 3.0f;

        if (m_shake_time <= 0.0f)
        {
            m_screen_shaking = false;
            m_shake_time = 0.0f;
            m_background_y_pos = 0.0f;
        }
    }
}
