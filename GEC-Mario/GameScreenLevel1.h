#pragma once

#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreenLevelBase.h"

class Texture2D;
class SoundEffect;
class PowBlock;
class GameScreenManager;

class GameScreenLevel1 : public GameScreenLevelBase
{
private:
    PowBlock* m_pow_block;
    
    int m_enemy_spawn_side;
    float m_enemy_spawn_timer;

    bool SetUpLevel() override;
	void SetUpEntities() override;

    void CheckPOWBlockCollisions(Character* character);
    void UpdateSpawners(float deltaTime);

public:
    GameScreenLevel1(SDL_Renderer* renderer, AudioManager* audio_manager, GameScreenManager* screen_manager, GameSession* session);
    ~GameScreenLevel1() override;

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
};

#endif
