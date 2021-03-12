#pragma once

#ifndef _CHARACTER_KOOPA_H
#define _CHARACTER_KOOPA_H

#include <string>

#include "Character.h"

class CharacterKoopa : public Character
{
private:
    float m_single_sprite_w;
    float m_single_sprite_h;

    bool m_injured;
    float m_injured_time;

    void ResetFlip();

public:
    CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, Facing start_facing, float movement_speed);
    ~CharacterKoopa();

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
    
    void TakeDamage();
    void Jump();

    Rect2D GetCollisionBox() override;
    bool IsInjured() { return m_injured; }
};

#endif
