#pragma once

#ifndef _ENEMY_KOOPA_H
#define _ENEMY_KOOPA_H

#include <string>

#include "Enemy.h"
#include "SoundEffect.h"

class EnemyKoopa : public Enemy
{
private:
    float m_single_sprite_w;
    float m_single_sprite_h;

    float GetWidth() override { return m_single_sprite_w; }
    float GetHeight() override { return m_single_sprite_h; }

public:
    EnemyKoopa(SDL_Renderer* renderer, std::string imagePath, SoundEffect* stomp_sound, LevelMap* map, Vector2D start_position, Facing start_facing);
    ~EnemyKoopa();

    void Render() override;
    void DoAIMove() override;

    int GetKillScore() override;
};

#endif
