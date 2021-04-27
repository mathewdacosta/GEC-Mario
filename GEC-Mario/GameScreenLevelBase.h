#pragma once

#include "Coin.h"
#include "GameScreen.h"
#include "LevelMap.h"
#include "PlayerMario.h"
#include "PlayerLuigi.h"
#include "EnemyKoopa.h"
#include "GameScreenManager.h"
#include "TextBox.h"


class GameScreenLevelBase : public GameScreen
{
private:
	void CheckPlayerEnemyCollision(Player* player, Enemy* enemy);

protected:
    const std::string m_bg_image_path;
    const std::string m_fg_image_path;
	const std::string m_tile_image_path;
    const std::string m_bg_music_path;
    const std::string m_level_map_path;

	GameScreenManager* m_screen_manager;

	LevelMap* m_level_map;
    Texture2D* m_background_texture;
	Texture2D* m_overlay_texture;
	Texture2D* m_tiles_spritesheet;
	AnimatedSprite* m_floor_tile;

	Font* m_hud_font;
	TextBox* m_score_box;

    SoundEffect* m_coin_sound;
    SoundEffect* m_kick_sound;
    SoundEffect* m_mario_jump_sound;
    SoundEffect* m_luigi_jump_sound;
    SoundEffect* m_stomp_sound;

    PlayerMario* m_character_mario;
    PlayerLuigi* m_character_luigi;
    std::vector<Enemy*> m_enemies;
	std::vector<Coin*> m_coins;

    bool m_screen_shaking;
    float m_shake_time;
    float m_wobble;
    float m_background_y_pos;

	GameScreenLevelBase(SDL_Renderer* renderer, AudioManager* audio_manager, GameScreenManager* screen_manager, GameSession* session, std::string bg_image_path, std::string fg_image_path, std::string tile_image_path, std::string bg_music_path, std::string level_map_path);
    ~GameScreenLevelBase();
	
    virtual bool SetUpLevel();
    virtual void SetUpEntities() = 0;
	
    void SetLevelMap();
    void SetUpSFX();

    void CreateMario(Vector2D position);
    void CreateLuigi(Vector2D position);
    void CreateKoopa(Vector2D position, Facing direction, float speed);
	void CreateCoin(Vector2D position, Vector2D force);
	
	void CheckPlayersAlive();
    void DoScreenShake();
    void RenderLevelMapTiles() const;
    void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void UpdateScoreText();

public:
	bool Setup() override;
	void Render() override;
};

