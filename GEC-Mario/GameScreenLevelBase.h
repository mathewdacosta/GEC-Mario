#pragma once

#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"


class GameScreenLevelBase : public GameScreen
{
protected:
    const std::string m_bg_image_path;
    const std::string m_bg_music_path;
    const std::string m_level_map_path;

    LevelMap* m_level_map;
    Texture2D* m_background_texture;

    SoundEffect* m_coin_sound;
    SoundEffect* m_kick_sound;
    SoundEffect* m_mario_jump_sound;
    SoundEffect* m_luigi_jump_sound;
    SoundEffect* m_stomp_sound;

    CharacterMario* m_character_mario;
    CharacterLuigi* m_character_luigi;
    std::vector<CharacterKoopa*> m_enemies;

    bool m_screen_shaking;
    float m_shake_time;
    float m_wobble;
    float m_background_yPos;
	
	GameScreenLevelBase(SDL_Renderer* renderer, AudioManager* audio_manager, std::string bg_image_path, std::string bg_music_path, std::string level_map_path);
    ~GameScreenLevelBase();
	
    virtual bool SetUpLevel();
    virtual void SetUpEntities() = 0;
	
    void SetLevelMap();
    void SetUpSFX();

    void CreateMario(Vector2D position);
    void CreateLuigi(Vector2D position);
    void CreateKoopa(Vector2D position, Facing direction, float speed);
	
    void DoScreenShake();
    void RenderLevelMapDebugGrid() const;
    void UpdateEnemies(float deltaTime, SDL_Event e);

public:
	bool Setup() override;
	
};

