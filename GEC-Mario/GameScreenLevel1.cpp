#include "GameScreenLevel1.h"

#include <iostream>

#include "Collisions.h"
#include "Texture2D.h"
#include "PowBlock.h"
#include "SoundEffect.h"

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

	if (!SetBGM("Audio/Music/Mario.mp3"))
	{
		return false;
	}

    // Set level map
	SetLevelMap();

	// Load sound effects
	SetUpSFX();

    // Create characters and POW block
	SetUpEntities();

	// Set up spawner variables
	m_enemy_spawn_side = 0;
	m_enemy_spawn_timer = LEVEL_1_SPAWNER_DELAY;
    
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

void GameScreenLevel1::SetUpEntities()
{
	m_character_mario = new CharacterMario(m_renderer, Vector2D(64, 300), m_level_map);
	m_character_luigi = new CharacterLuigi(m_renderer, Vector2D(256, 280), m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CreateKoopa(Vector2D(150, 32), Facing::RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), Facing::LEFT, KOOPA_SPEED);
}

void GameScreenLevel1::SetUpSFX()
{
	m_coin_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_coin.wav", 0);
	m_kick_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_kick.wav", 0);
	m_mario_jump_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_jump-small.wav", 1);
	m_luigi_jump_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_jump-super.wav", 2);
	m_stomp_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_stomp.wav", 3);
}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, AudioManager* audio_manager) : GameScreen(renderer, audio_manager)
{
    SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
    delete m_background_texture;
    delete m_character_mario;
    delete m_character_luigi;
    delete m_pow_block;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
    m_enemies.clear();

	delete m_coin_sound;
	delete m_kick_sound;
	delete m_mario_jump_sound;
	delete m_luigi_jump_sound;
	delete m_stomp_sound;
}

void GameScreenLevel1::Render()
{
    // Draw background texture
    m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

    // Draw characters and POW block
    m_character_mario->Render();
    m_character_luigi->Render();
    m_pow_block->Render();

	for (int i = 0; i < m_enemies.size(); i++)
	{
        m_enemies[i]->Render();
	}

    // RenderDebugGrid();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
    m_character_mario->Update(deltaTime, e);
    m_character_luigi->Update(deltaTime, e);
    UpdatePOWBlock();
    UpdateEnemies(deltaTime, e);
	UpdateSpawners(deltaTime);

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

	// Damage any enemies on screen
	for (int i = 0; i < m_enemies.size(); i++)
	{
        m_enemies[i]->TakeDamage();
	}
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

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		// index of enemy to delete at end; -1 signifies none to delete
        int toDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
            CharacterKoopa* current = m_enemies[i];

			Rect2D collisionBox = current->GetCollisionBox();
            float posX = collisionBox.x;
            float posY = collisionBox.y;
			float width = collisionBox.width;
			
			// Check whether enemy is on bottom row of tiles
			if (posY > 300.0f)
			{
				// Check if enemy is off either left or right of screen
				if (posX < (float) (width * 0.5f) || posX > SCREEN_WIDTH - (float) (width * 0.5f))
				{
					// Kill enemy if off screen
                    current->SetAlive(false);
				}
				
				// Call enemy update method
				current->Update(deltaTime, e);
			}
			else
			{
				// Check if enemy is off either left or right of screen and wrap around
				if (posX < (float) -(width * 0.5f))
				{
					current->SetPosition(Vector2D(SCREEN_WIDTH - (0.5 * width), posY));
				}
				else if (posX > SCREEN_WIDTH - (float) (width * 0.5f))
				{
					current->SetPosition(Vector2D(0.5 * width, posY));
				}
				else
				{
					// Call enemy update method
					current->Update(deltaTime, e);
				}
			}

			// Check enemy collisions if enemy is not behind pipe
			if (!((posY > 300.0f || posY <= 64.0f) && (posX <  64.0f || posX > SCREEN_WIDTH - 96.0f)))
            {
	            if (Collisions::Instance()->Circle(current, m_character_mario))
	            {
		            if (current->IsInjured())
		            {
		            	// Kill enemy when collided
                        current->SetAlive(false);
		            	m_kick_sound->Play();
		            }
                    else
                    {
	                    // TODO: kill mario
                    }
	            }
            }

			// Check whether enemy is dead and schedule for deletion
			if (!current->IsAlive())
			{
                toDelete = i;
			}
		}

		// Remove enemy if scheduled (will be last if multiple are dead)
		if (toDelete >= 0)
		{
			CharacterKoopa* temp = m_enemies[toDelete];
            m_enemies.erase(m_enemies.begin() + toDelete);
			delete temp;
		}
	}
}

void GameScreenLevel1::UpdateSpawners(float deltaTime)
{
	m_enemy_spawn_timer -= deltaTime;
	if (m_enemy_spawn_timer <= 0.0f)
	{
		Vector2D position;
		Facing direction;
		if (m_enemy_spawn_side == 0)
		{
			position = LEVEL_1_SPAWNER_POSITION_0;
			direction = Facing::RIGHT;
		}
		else
		{
			position = LEVEL_1_SPAWNER_POSITION_1;
			direction = Facing::LEFT;
		}

		CreateKoopa(position, direction, KOOPA_SPEED);

		m_enemy_spawn_side = (m_enemy_spawn_side + 1) % 2;
		m_enemy_spawn_timer = LEVEL_1_SPAWNER_DELAY;
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, Facing direction, float speed)
{
    CharacterKoopa* enemy = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_stomp_sound, m_level_map, position, direction, speed);
    m_enemies.push_back(enemy);
}


