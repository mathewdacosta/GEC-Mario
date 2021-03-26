#pragma once

#include <vector>

#include "CharacterKoopa.h"
#include "GameScreen.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"

#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

class Texture2D;
class SoundEffect;
class PowBlock;

class GameScreenLevel1 : public GameScreen
{
private:
    LevelMap* m_level_map;
    
    Texture2D* m_background_texture;
    
    SoundEffect* m_coin_sound;
    SoundEffect* m_kick_sound;
    SoundEffect* m_mario_jump_sound;
    SoundEffect* m_luigi_jump_sound;
    SoundEffect* m_stomp_sound;
    
    CharacterMario* m_character_mario;
    CharacterLuigi* m_character_luigi;
    PowBlock* m_pow_block;
    std::vector<CharacterKoopa*> m_enemies;

    int m_enemy_spawn_side;
    float m_enemy_spawn_timer;

    bool m_screen_shaking;
    float m_shake_time;
    float m_wobble;
    float m_background_yPos;

    bool SetUpLevel();
    void SetLevelMap();
    void SetUpEntities();
    void SetUpSFX();
    void CreateKoopa(Vector2D position, Facing direction, float speed);

    void UpdatePOWBlock();
    void DoScreenShake();
    void RenderDebugGrid();
    void UpdateEnemies(float deltaTime, SDL_Event e);
    void UpdateSpawners(float deltaTime);

public:
    GameScreenLevel1(SDL_Renderer* renderer, AudioManager* audio_manager);
    ~GameScreenLevel1();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
};

#endif
