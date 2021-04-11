#include "GameScreenLevelBase.h"

#include <iostream>


#include "Collisions.h"
#include "Texture2D.h"
#include "SoundEffect.h"

GameScreenLevelBase::GameScreenLevelBase(SDL_Renderer* renderer, AudioManager* audio_manager, std::string bg_image_path, std::string bg_music_path, std::string level_map_path) :
	GameScreen(renderer, audio_manager),
	m_bg_image_path(bg_image_path),
	m_bg_music_path(bg_music_path),
	m_level_map_path(level_map_path)
{
	// Initialise screen shake variables
	m_screen_shaking = false;
	m_shake_time = SCREEN_SHAKE_DURATION;
	m_wobble = 0.0f;
	m_background_yPos = 0.0f;

	// Initialise level map to nullptr
	m_level_map = nullptr;
}

GameScreenLevelBase::~GameScreenLevelBase()
{
	delete m_background_texture;
	delete m_character_mario;
	delete m_character_luigi;

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


bool GameScreenLevelBase::Setup()
{
	return this->SetUpLevel();
}

bool GameScreenLevelBase::SetUpLevel()
{
	// Load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile(m_bg_image_path))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	if (!SetBGM(m_bg_music_path))
	{
		return false;
	}

	// Set level map
	SetLevelMap();

	// Load sound effects
	SetUpSFX();

	// Create characters and POW block
	SetUpEntities();
}

void GameScreenLevelBase::SetLevelMap()
{
	// Delete old map if still exists
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	// Set new map
	m_level_map = LevelMap::LoadFromFile(m_level_map_path);
}

void GameScreenLevelBase::SetUpSFX()
{
	m_coin_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_coin.wav", 0);
	m_kick_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_kick.wav", 0);
	m_mario_jump_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_jump-small.wav", 1);
	m_luigi_jump_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_jump-super.wav", 2);
	m_stomp_sound = new SoundEffect(m_audio_manager, "Audio/SFX/smb_stomp.wav", 3);
}

void GameScreenLevelBase::CreateMario(Vector2D position)
{
	m_character_mario = new CharacterMario(m_renderer, position, m_level_map, m_mario_jump_sound);
}

void GameScreenLevelBase::CreateLuigi(Vector2D position)
{
	m_character_luigi = new CharacterLuigi(m_renderer, position, m_level_map, m_luigi_jump_sound);
}

void GameScreenLevelBase::CreateKoopa(Vector2D position, Facing direction, float speed)
{
	CharacterKoopa* enemy = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_stomp_sound, m_level_map, position, direction, speed);
	m_enemies.push_back(enemy);
}

void GameScreenLevelBase::DoScreenShake()
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

void GameScreenLevelBase::RenderLevelMapDebugGrid() const
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

void GameScreenLevelBase::UpdateEnemies(float deltaTime, SDL_Event e)
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
				if (posX < (float)(width * 0.5f) || posX > SCREEN_WIDTH - (float)(width * 0.5f))
				{
					// Kill enemy if off screen
					current->SetAlive(false);
				}
			}
			
			// Call enemy update method
			current->Update(deltaTime, e);

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
				else if (Collisions::Instance()->Circle(current, m_character_luigi))
				{
					if (current->IsInjured())
					{
						// Kill enemy when collided
						current->SetAlive(false);
						m_kick_sound->Play();
					}
					else
					{
						// TODO: kill luigi
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


