#pragma once

#ifndef _ENEMY_KOOPA_H
#define _ENEMY_KOOPA_H

#include <string>

#include "Enemy.h"
#include "SoundEffect.h"

class EnemyKoopa : public Enemy
{
protected:
    void ResetFlip() override;

public:
    EnemyKoopa(SDL_Renderer* renderer, std::string imagePath, SoundEffect* stomp_sound, LevelMap* map, Vector2D start_position, Facing start_facing);
    ~EnemyKoopa();

    void Update(float deltaTime, SDL_Event e) override;
    void Render() override;
    
    void DoAIMove() override;
    void TakeDamage() override;

    int GetKillScore() override;
};

#endif
