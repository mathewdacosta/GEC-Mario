#include "GameScreenLevelBase.h"

#include <iostream>
#include <iomanip>
#include <sstream>


#include "AnimatedSprite.h"
#include "Collisions.h"
#include "Font.h"
#include "Texture2D.h"
#include "SoundEffect.h"
#include "TextBox.h"

GameScreenLevelBase::GameScreenLevelBase(SDL_Renderer* renderer, AudioManager* audio_manager, GameScreenManager* screen_manager, GameSession* session, std::string bg_image_path, std::string fg_image_path, std::string tile_image_path, std::string bg_music_path, std::string level_map_path) :
	GameScreen(renderer, audio_manager, session),
	m_bg_image_path(bg_image_path),
	m_fg_image_path(fg_image_path),
	m_tile_image_path(tile_image_path),
	m_bg_music_path(bg_music_path),
	m_level_map_path(level_map_path),
	m_screen_shaking(false),
	m_shake_time(SCREEN_SHAKE_DURATION),
	m_wobble(0.0f),
	m_screen_manager(screen_manager)
{
	// Initialise screen shake variables
	m_screen_shaking = false;
	m_shake_time = SCREEN_SHAKE_DURATION;
	m_wobble = 0.0f;
	m_background_y_pos = 0.0f;

	// Initialise level map to nullptr
	m_level_map = nullptr;
}

GameScreenLevelBase::~GameScreenLevelBase()
{
	delete m_background_texture;
	delete m_overlay_texture;
	delete m_tiles_spritesheet;
	delete m_floor_tile;
	delete m_hud_font;
	delete m_score_box;
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

void GameScreenLevelBase::CheckPlayerEnemyCollision(Player* player, Enemy* enemy)
{
	if (Collisions::Instance()->Circle(enemy, player))
	{
		if (enemy->IsInjured())
		{
			// Kill enemy when collided
			enemy->SetAlive(false);
			m_kick_sound->Play();
			m_session->score += enemy->GetKillScore();
		}
		else
		{
			// Kill player
			player->Kill();
		}
	}
	// Check ceiling headbutt
	else if (player->IsHeadbuttingCeiling())
	{
		Rect2D impactArea = player->GetCollisionBox();
		impactArea.y -= impactArea.height * 1.5f;
		if (Collisions::Instance()->Box(enemy->GetCollisionBox(), impactArea))
		{
			if (!enemy->IsInjured())
			{
				// Make enemy take damage
				enemy->TakeDamage();
				// Spawn coin
				Vector2D coinForce = {
					((rand() % 5) - 2.5f) * 60.0f,
					280.0f
				};
				CreateCoin(enemy->GetPosition(), coinForce);
			}
		}
	}
}

bool GameScreenLevelBase::Setup()
{
	return this->SetUpLevel();
}

void GameScreenLevelBase::Render()
{
	// Draw background texture
	m_background_texture->Render({ 0, m_background_y_pos }, SDL_FLIP_NONE);

	// Draw level map tiles
	RenderLevelMapTiles();

	// Draw characters
	m_character_mario->Render();
	m_character_luigi->Render();

	// Draw enemies
	for (int i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->Render();

	// Draw coins
	for (int i = 0; i < m_coins.size(); i++)
		m_coins[i]->Render();

	// Draw overlay
	m_overlay_texture->Render({ 0, m_background_y_pos }, SDL_FLIP_NONE);

	m_score_box->Draw();
}

bool GameScreenLevelBase::SetUpLevel()
{
	// Load background and foreground textures
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile(m_bg_image_path))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	m_overlay_texture = new Texture2D(m_renderer);
	if (!m_overlay_texture->LoadFromFile(m_fg_image_path))
	{
		std::cout << "Failed to load overlay texture!" << std::endl;
		return false;
	}

	m_tiles_spritesheet = new Texture2D(m_renderer);
	if (!m_tiles_spritesheet->LoadFromFile(m_tile_image_path))
	{
		std::cout << "Failed to load tile spritesheet texture!" << std::endl;
		return false;
	}

	m_floor_tile = new AnimatedSprite(m_renderer, m_tiles_spritesheet, TILE_WIDTH, TILE_HEIGHT);

	if (!SetBGM(m_bg_music_path))
	{
		return false;
	}

	m_hud_font = new Font(m_renderer, "Fonts/Super-Mario-World.ttf", 14);
	if (!m_hud_font->IsLoaded())
	{
		// Already logged - just return
		return false;
	}

	// Ensure we have at least 1 player
	if (m_session->players < 1)
		m_session->players = 1;

	// Set up score HUD
	m_score_box = new TextBox(m_hud_font, "SCORE  ", { 20, 400 }, TextColor::WHITE, TextColor::BLACK, true, TextAlignHorizontal::LEFT, TextAlignVertical::CENTER);

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
	m_character_mario = new PlayerMario(m_renderer, position, m_level_map, m_mario_jump_sound);
}

void GameScreenLevelBase::CreateLuigi(Vector2D position)
{
	m_character_luigi = new PlayerLuigi(m_renderer, position, m_level_map, m_luigi_jump_sound);
}

void GameScreenLevelBase::CreateKoopa(Vector2D position, Facing direction, float speed)
{
	EnemyKoopa* enemy = new EnemyKoopa(m_renderer, "Images/Koopa.png", m_stomp_sound, m_level_map, position, direction);
	m_enemies.push_back(enemy);
}

void GameScreenLevelBase::CreateCoin(Vector2D position, Vector2D force)
{
	Coin* coin = new Coin(m_renderer, position, force, m_level_map);
	m_coins.push_back(coin);
}

void GameScreenLevelBase::CheckPlayersAlive()
{
	if (m_character_mario->IsGameOver() && m_character_luigi->IsGameOver())
	{
		m_screen_manager->QueueScreen(Screen::GAME_OVER);
	}
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

void GameScreenLevelBase::RenderLevelMapTiles() const
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			Vector2D tilePos = { (float) i * TILE_WIDTH, (float) j * TILE_HEIGHT };
			
			switch (m_level_map->GetTileAt(j, i))
			{
			case 0:
				SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
				break;
			case 1:
				m_floor_tile->Draw(tilePos);
				SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
				break;
			default:
				SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
				break;
			}
			
#ifdef DEBUG_DRAW_TILES
			SDL_Rect current_rect = {
				i * TILE_WIDTH,
                j * TILE_HEIGHT,
                TILE_WIDTH,
                TILE_HEIGHT
            };
			
			SDL_RenderDrawRect(m_renderer, &current_rect);
#endif
		}
	}
}

void GameScreenLevelBase::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (m_enemies.empty())
	{
		return;
	}
	
	// index of enemy to delete at end; -1 signifies none to delete
	int toDelete = -1;
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		Enemy* current = m_enemies[i];

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

		// Check enemy collisions if enemy is not behind pipe
		if (!((posY > 300.0f || posY <= 64.0f) && (posX <  64.0f || posX > SCREEN_WIDTH - 96.0f)))
		{
			CheckPlayerEnemyCollision(m_character_mario, current);
			CheckPlayerEnemyCollision(m_character_luigi, current);
		}
		
		// Call enemy update method
		current->Update(deltaTime, e);

		// Check whether enemy is dead and schedule for deletion
		if (!current->IsAlive())
		{
			toDelete = i;
		}
	}

	// Remove enemy if scheduled (will be last if multiple are dead)
	if (toDelete >= 0)
	{
		Enemy* temp = m_enemies[toDelete];
		m_enemies.erase(m_enemies.begin() + toDelete);
		delete temp;
	}
}

void GameScreenLevelBase::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (m_coins.empty())
	{
		return;
	}

	int toDelete = -1;
	for (int i = 0; i < m_coins.size(); i++)
	{
		Coin* current = m_coins[i];
		current->Update(deltaTime, e);

		if (current->IsAlive())
		{
			if (Collisions::Instance()->Circle(m_coins[i], m_character_mario) || Collisions::Instance()->Circle(m_coins[i], m_character_luigi))
			{
				// Delete coin
				current->SetAlive(false);

				// Increment score and play sound
				m_coin_sound->Play();
				m_session->score += COIN_COLLECT_SCORE;
			}

			if (current->GetLifetime() > COIN_MAX_LIFETIME)
			{
				current->SetAlive(false);
			}
		}
		else
		{
			// Queue for deletion
			toDelete = i;
		}
	}

	if (toDelete > -1)
	{
		Coin* temp = m_coins[toDelete];
		m_coins.erase(m_coins.begin() + toDelete);
		delete temp;
	}
}

void GameScreenLevelBase::UpdateScoreText()
{
	std::stringstream score;
	score << "SCORE   " << std::setw(8) << std::setfill('0') << m_session->score;
	m_score_box->SetText(score.str());
}
